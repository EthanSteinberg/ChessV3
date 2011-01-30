#include "chessNet.h"

#include "../messages.h"

using namespace boost::asio::ip;

t_chessNet::t_chessNet(t_sharedData &theSharedData) : sharedData(theSharedData) , socket(io_service)
{
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
         std::cout<<"The name was: "<<message.joinServer.name<<" at a port of: "<<message.joinServer.address<<endl;
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
}
