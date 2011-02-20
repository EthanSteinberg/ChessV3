#include <iostream>

#include <boost/thread.hpp>
#include <boost/foreach.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessGame.h"
#include "messages.h"

bool t_chessGame::processMessageServer(const t_message &message)
{
   switch (message.id)
   {

   case BOARD_CLICKED:
   {
      printf("The turn was %d\n",message.boardClicked.turn);

      std::vector<t_message> messageBuffer = chessEngine.boardClickedSingle(message);

         BOOST_FOREACH(t_message &newMessage, messageBuffer)
         {
            sharedGame.pushToBoth(newMessage);
         }

      break;
   }

   case QUIT_MESSAGE:
   {
      std::cout<<"Cli told to quit"<<std::endl;

      sharedGame.pushToBoth(message);
   }
   return 1;

   default:
      std::cout<<"And I do not know what it was"<<std::endl;

   }

   return 0;
}
