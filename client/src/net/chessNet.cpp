#include "chessNet.h"

#include "messages.h"
#include "netMessages.h"

#include <iostream>

#include <string>

using namespace boost::asio::ip;

t_chessNet::t_chessNet(t_sharedData &theSharedData) : sharedData(theSharedData) , socket(io_service)
{
   //tcp::no_delay option(true);
   //socket.set_option(option);

   //boost::asio::socket_base::non_blocking_io option2(true);
   //socket.io_control(option2);

}

void t_chessNet::run()
{
   for (;;)
   {
      t_message message;
      {
         boost::unique_lock<boost::mutex> lock(sharedData.netMutex);

         if (sharedData.netBuffer.empty())
         {
            sharedData.netCondition.wait(lock);
         }

         message = sharedData.netBuffer.back();
         sharedData.netBuffer.pop_back();
      }
      std::cout<<"I have recieved a message"<<std::endl;

      switch (message.id)
      {
      case JOIN_SERVER:
      {
         std::cout<<"The name was: "<<message.joinServer.name<<" at a port of: "<<message.joinServer.address<<std::endl;
         connected(message.joinServer.name,message.joinServer.address);
         return;
      }

      case QUIT_MESSAGE:
         std::cout<<"It told me to quit"<<std::endl;
         return;

      default:
         std::cout<<"And I do not know what it was"<<std::endl;
      }
   }
}


void t_chessNet::connected(const std::string &name, const std::string &address)
{
   tcp::resolver resolver(io_service);
   tcp::resolver::query query(tcp::v4(), address, "1510");
   tcp::resolver::iterator iterator = resolver.resolve(query);

   socket.connect(*iterator);

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

            t_netMessage newNetMessage;
            newNetMessage.id = NET_REFRESH_CONNECTION;

            socket.send(boost::asio::buffer(&newNetMessage,sizeof(newNetMessage)));
            break;
         }

         case QUIT_MESSAGE:
         {
            std::cout<<"It told me to quit"<<std::endl;

            t_netMessage newNetMessage;
            newNetMessage.id = NET_QUIT_MESSAGE;

            socket.send(boost::asio::buffer(&newNetMessage,sizeof(newNetMessage)));

            return;
         }
         default:
            std::cout<<"And I do not know what it was"<<std::endl;
         }
      }

      for (;;)
      {
         boost::system::error_code ec;

         if (!socket.available(ec))
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
         

      case NET_QUIT_MESSAGE:
         std::cout<<"It told me to quit"<<std::endl;
         return;

      default:
         std::cout<<"And I do not know what it was"<<std::endl;
      }
   }
}

}
