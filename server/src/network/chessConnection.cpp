#include "chessConnection.h"

#include "messages.h"
#include "netMessages.h"
#include <boost/shared_ptr.hpp>

#include <iostream>

#include <boost/thread.hpp>

using namespace boost::asio::ip;

t_chessConnection::t_chessConnection(t_connectionData &theSharedData, const boost::shared_ptr<tcp::socket> &theSocket) : connectionData(theSharedData), socket(theSocket)
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
            boost::unique_lock<boost::mutex> lock(connectionData.connMutex);

            if (connectionData.connBuffer.empty())
            {
               break;
            }

            message = connectionData.connBuffer.back();
            connectionData.connBuffer.pop_back();
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
         {   break;}



         std::cout<<"About to read the the connection that \"should\" be there...   "<<ec<<std::endl;

         t_netMessage netMessage;

         socket->read_some(boost::asio::buffer(&netMessage,sizeof(netMessage)));
         switch (netMessage.id)
         {
         case NET_JOIN_SERVER:
         {
            std::cout<<"The name was: "<<netMessage.netJoinServer.name<<std::endl;
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
