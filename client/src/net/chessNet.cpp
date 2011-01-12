#include "chessNet.h"
#include <iostream>

t_chessNet::t_chessNet(t_sharedData &theSharedData) : sharedData(theSharedData)
{}

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

      case CONNECT_SERVER:
         std::cout<<"Connecting to server"<<std::endl;

      case QUIT_MESSAGE:
         std::cout<<"It told me to quit"<<std::endl;
         return;

      default:
         std::cout<<"And I do not know what it was"<<std::endl;
      }
   }

}
