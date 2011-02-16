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
         int quit = connected(message.joinServer.name,message.joinServer.address);

         t_message newMessage;
         newMessage.id = CONNECTION_FAILED;
            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(newMessage);
            }

            sharedData.gameCondition.notify_one();

         if (quit == 1)
            return;

         break;
      }

      case QUIT_MESSAGE:
         std::cout<<"It told me to quit"<<std::endl;
         return;

      default:
         std::cout<<"And I do not know what it was"<<std::endl;
      }
   }
}


