#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessCli.h"
#include "messages.h"

t_chessCli::t_chessCli(t_sharedGame &theSharedGame) : sharedGame(theSharedGame), selected(0)
{
   std::cout<<"Hello world"<<std::endl;

   board =
   {
      {10, 11, 12, 14, 13, 12, 11, 10},
      { 9,  9,  9,  9,  9,  9,  9,  9},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 1,  1,  1,  1,  1,  1,  1,  1},
      { 2,  3,  4,  6,  5,  4,  3,  2}
   };

   whiteCanCastleLeft = 1;
   whiteCanCastleRight = 1;

   blackCanCastleLeft = 1;
   blackCanCastleRight = 1;

   turn = 0;

   whiteKingPos.x = 4;
   blackKingPos.x = 4;

   whiteKingPos.y = 7;
   blackKingPos.y = 0;


   t_myVector2 pos;

   for (int y = 6; y < 8; y++)
   {
      pos.y = y;

      for (int x = 0; x<8; x++)
      {
         pos.x = x;
         whitePieces.insert(pos);
      }
   }

   for (int y = 0; y < 2; y++)
   {
      pos.y = y;

      for (int x = 0; x<8; x++)
      {
         pos.x = x;
         blackPieces.insert(pos);
      }
   }
}

void t_chessCli::run()
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




