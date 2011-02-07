#include "chessConnection.h"

#include "messages.h"
#include "netMessages.h"
#include "myDataBase.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>

#include <iostream>

#include <boost/thread.hpp>

using namespace boost::asio::ip;

t_chessConnection::t_chessConnection(boost::shared_ptr<t_connectionData> theSharedData, const boost::shared_ptr<tcp::socket> &theSocket, tcp::endpoint theEnd) : connectionData(theSharedData), socket(theSocket), end(theEnd)
{
   std::cout<<"Connection made !!"<<std::endl;
}

void t_chessConnection::run()
{

   for (;;)
   {
      boost::this_thread::sleep(boost::posix_time::seconds(1));

      for (;;)
      {
         t_message message;
         {
            boost::unique_lock<boost::mutex> lock(connectionData->connMutex);

            if (connectionData->connBuffer.empty())
            {
               break;
            }

            message = connectionData->connBuffer.back();
            connectionData->connBuffer.pop_back();
         }
         std::cout<<"I have recieved a message"<<std::endl;

         switch (message.id)
         {
         case JOIN_SERVER:
         {
            std::cout<<"The name was: "<<message.joinServer.name<<" at a port of: "<<message.joinServer.address<<std::endl;
            break;
         }

         case QUIT_MESSAGE:
            std::cout<<"It told me to quit"<<std::endl;
            return;

         default:
            std::cout<<"And I do not know what it was"<<std::endl;
         }
      }

      for (;;)
      {


         boost::system::error_code ec;

         if (!socket->available(ec))
         {
            break;
         }



         std::cout<<"About to read the the connection that \"should\" be there...   "<<ec<<std::endl;

         t_netMessage netMessage;

         socket->read_some(boost::asio::buffer(&netMessage,sizeof(netMessage)));

         switch (netMessage.id)
         {
         case NET_JOIN_SERVER:
         {
            std::cout<<"The name was: "<<netMessage.netJoinServer.name<<std::endl;


            //std::pair<tcp::endpoint, boost::shared_ptr<t_myData> > myDataTemp;
            int found = 0;

            {
               boost::unique_lock<boost::shared_mutex> lock(connectionData->myDataInfo->myDataMutex);

               BOOST_FOREACH( auto myDataTemp,  connectionData->myDataInfo->myDataBase)
               {
                  if (!myDataTemp.second)
                     continue;

                  if (myDataTemp.second->name == std::string(netMessage.netJoinServer.name))
                  {
                     found = 1;
                     break;
                  }
               }

            }

            if (found == 1)
            {
               t_netMessage newNetMessage;

               newNetMessage.id = NET_CONNECTION_BAD_NAME;
               socket->send(boost::asio::buffer(&newNetMessage,sizeof(newNetMessage)));
               return;
            }


            boost::shared_ptr<t_myData> myData = boost::make_shared<t_myData>();

            myData->name = netMessage.netJoinServer.name;
            myData->wins = 0;
            myData->losses = 0;
            myData->status = NOTHING;
            myData->connectionData = connectionData;

            {
               boost::unique_lock<boost::shared_mutex> lock(connectionData->myDataInfo->myDataMutex);

               connectionData->myDataInfo->myDataBase.insert(std::make_pair(end,myData));
            }

            t_netMessage newNetMessage;

            newNetMessage.id = NET_CONNECTION_SUCCESS;
            socket->send(boost::asio::buffer(&newNetMessage,sizeof(newNetMessage)));

            break;
         }

         case NET_REFRESH_CONNECTION:
         {
            std::cout<<"Now I have to send the stupid data over the internet, stupid net"<<std::endl;

            {
               boost::shared_lock<boost::shared_mutex> lock(connectionData->myDataInfo->myDataMutex);

               netMessage.netRefreshConnection.numOfPackets = connectionData->myDataInfo->myDataBase.size();

               socket->send(boost::asio::buffer(&netMessage,sizeof(netMessage)));
               t_dataPacket dataPacket;

               for (auto iter = connectionData->myDataInfo->myDataBase.begin(); iter != connectionData->myDataInfo->myDataBase.end(); iter++)
               {
                  strcpy(dataPacket.name,iter->second->name.c_str());
                  dataPacket.wins = iter->second->wins;
                  dataPacket.losses = iter->second->losses;
                  dataPacket.status = iter->second->status;

                  socket->send(boost::asio::buffer(&dataPacket,sizeof(dataPacket)));

               }

            }

            break;
         }


         case NET_QUIT_MESSAGE:
            std::cout<<"It told me to quit"<<std::endl;
            return;


         default:
            std::cout<<"And I do not know what it was"<<std::endl;
         }
      }
   }

   std::cout<<"The thread started, then quit"<<std::endl;


}
