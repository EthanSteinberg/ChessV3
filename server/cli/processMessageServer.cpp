#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessCli.h"
#include "messages.h"

bool t_chessCli::processMessageServer(const t_message &message)
{
   switch (message.id)
   {

   case BOARD_CLICKED:
   {
      std::cout<<"The cli knows the board has been clicked"<<std::endl;
      boardClickedServer(message);
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
