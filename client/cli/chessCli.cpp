#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessCli.h"
#include "messages.h"

t_chessCli::t_chessCli(t_sharedData &theSharedData) : sharedData(theSharedData),  connected(0), status(NOTHING)
{
   chessEngine.reset();
}

void t_chessCli::run()
{
   for (;;)
   {
      t_message message;

      {
         boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

         while (sharedData.gameBuffer.empty())
         {
            sharedData.gameCondition.wait(lock);
         }

         message = sharedData.gameBuffer.back();
         sharedData.gameBuffer.pop_back();

      }

      std::cout<<"I have recieved a message"<<std::endl;
      
      int quit;
      
      if (!connected)
         quit = processMessageSingle(message);

      else
         quit = processMessageConnected(message);

      if (quit)
         return;

   }
}




