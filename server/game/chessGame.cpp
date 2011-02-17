#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessGame.h"
#include "messages.h"

t_chessGame::t_chessGame(t_sharedGame &theSharedGame) : sharedGame(theSharedGame)
{}

void t_chessGame::run()
{
   for (;;)
   {
      t_message message;

      {
         boost::unique_lock<boost::mutex> lock(sharedGame.gameMutex);

         if (sharedGame.gameBuffer.empty())
         {
            sharedGame.gameCondition.wait(lock);
         }

         message = sharedGame.gameBuffer.back();
         sharedGame.gameBuffer.pop_back();

      }

      std::cout<<"I have recieved a message"<<std::endl;
      
      int quit;
      
      quit = processMessageServer(message);

      if (quit)
         return;

   }
}
