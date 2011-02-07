#include "chessNet.h"

#include "messages.h"
#include "netMessages.h"

#include <iostream>

#include <string>

using namespace boost::asio::ip;

void t_chessNet::connected(const std::string &name, const std::string &address)
{
   tcp::resolver resolver(io_service);
   tcp::resolver::query query(tcp::v4(), address, "1510");
   tcp::resolver::iterator iterator = resolver.resolve(query);

   boost::system::error_code ec;

   socket.connect(*iterator,ec);

   if (ec)
   {

      if (ec.value() == boost::system::errc::connection_refused)
      {
            std::cout<<"Connection fail"<<std::endl;

            t_message message;
            message.id = CONNECTION_NO_SERVER;


            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         return;
      }

      else
      {
         std::cout<<ec.message()<<std::endl;
         std::cout<<ec.value()<<std::endl;

         exit(1);
      }
   }

   t_netMessage newNetMessage;
   newNetMessage.id = NET_JOIN_SERVER;
   strcpy(newNetMessage.netJoinServer.name,name.c_str());

   socket.send(boost::asio::buffer(&newNetMessage,sizeof(newNetMessage)));

   for (;;)
   {
      // socket.send(boost::asio::buffer(&newNetMessage,sizeof(newNetMessage)));
      for (;;)
      {
         t_message message;
         {
            boost::unique_lock<boost::mutex> lock(sharedData.netMutex);

            if (sharedData.netBuffer.empty())
            {
               break;
            }

            message = sharedData.netBuffer.back();
            sharedData.netBuffer.pop_back();
         }
         std::cout<<"I have recieved a message"<<std::endl;

         switch (message.id)
         {
         case JOIN_SERVER:
         {
            std::cout<<"The name was: "<<message.joinServer.name<<" at a port of: , but I am already connected"<<message.joinServer.address<<std::endl;
            break;
         }

         case WANT_REFRESH_CONNECTION:
         {
            std::cout<<"Net has to send the want for connection data over the interwebs"<<std::endl;

            t_netMessage aNewNetMessage;
            aNewNetMessage.id = NET_REFRESH_CONNECTION;

            socket.send(boost::asio::buffer(&aNewNetMessage,sizeof(aNewNetMessage)));
            break;
         }

         case QUIT_MESSAGE:
         {
            std::cout<<"It told me to quit"<<std::endl;

            t_netMessage aNewNetMessage;
            aNewNetMessage.id = NET_QUIT_MESSAGE;

            socket.send(boost::asio::buffer(&aNewNetMessage,sizeof(aNewNetMessage)));

            return;
         }
         default:
            std::cout<<"And I do not know what it was"<<std::endl;
         }
      }

      for (;;)
      {
         boost::system::error_code ecf;

         if (!socket.available(ecf))
         {
            break;
         }

         t_netMessage netMessage;

         socket.read_some(boost::asio::buffer(&netMessage,sizeof(netMessage)));

         switch (netMessage.id)
         {

         case NET_REFRESH_CONNECTION:
         {
            t_message message;

            message.id = REFRESH_CONNECTION;
            strcpy(message.refreshConnection.server,address.c_str());

            t_dataPacket dataPacket;

            std::cout<<"And the names come in: "<<std::endl;

            for (int i = 0; i<netMessage.netRefreshConnection.numOfPackets; i++)
            {
               socket.read_some(boost::asio::buffer(&dataPacket,sizeof(dataPacket)));
               std::cout<<dataPacket.name<<std::endl;

               message.dataPackets.push_back(dataPacket);
            }

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         }
         break;

         case NET_CONNECTION_SUCCESS:
         {
            std::cout<<"Connection success"<<std::endl;

            t_message message;
            message.id = CONNECTION_SUCCESS;


            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         }
         break;

         case NET_CONNECTION_BAD_NAME:
         {
            std::cout<<"Connection bad name"<<std::endl;

            t_message message;
            message.id = CONNECTION_BAD_NAME;


            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
            socket.close();
         }
         return;

         case NET_QUIT_MESSAGE:
            std::cout<<"It told me to quit"<<std::endl;
            return;

         default:
            std::cout<<"And I do not know what it was"<<std::endl;
         }
      }
   }

}
