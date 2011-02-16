#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessCli.h"
#include "messages.h"

void t_chessCli::boardClickedServer(const t_message &message)
{
   if (message.boardClicked.turn != turn)
   {
      std::cout<<"Wrong turn stupid"<<std::endl;
      return;
   }

   t_myVector2 pos = message.boardClicked.pos;
   std::cout<<"It was clicked at "<<pos<<std::endl;

   t_message newMessage;
   newMessage.id = HIGHLIGHT_SPACE;


   if (selected)
   {
      if (pos == selectedPos)
      {
         selected = 0;
         newMessage.highlightSpace.pos = selectedPos;
         newMessage.highlightSpace.color = 0;

         sharedGame.pushToOne(newMessage,turn);

         for (auto iter = move.begin(); iter != move.end(); iter++)
         {
            newMessage.highlightSpace.pos = *iter;
            newMessage.highlightSpace.color = 0;

            sharedGame.pushToOne(newMessage,turn);
         }

         for (auto iter = hit.begin(); iter != hit.end(); iter++)
         {
            newMessage.highlightSpace.pos = *iter;
            newMessage.highlightSpace.color = 0;

            sharedGame.pushToOne(newMessage,turn);
         }

         for (auto iter = castle.begin(); iter != castle.end(); iter++)
         {
            newMessage.highlightSpace.pos = *iter;
            newMessage.highlightSpace.color = 0;

            sharedGame.pushToOne(newMessage,turn);
         }

         move.clear();
         hit.clear();
         castle.clear();
      }

      else if (std::find(move.begin(), move.end(), pos) != move.end())
      {
         moveMove(pos);
      }

      else if (std::find(hit.begin(), hit.end(), pos) != hit.end())
      {
         attackMove(pos);
      }

      else if (std::find(castle.begin(), castle.end(), pos) != castle.end())
      {
         castleMove(pos);
      }
   }

   else if (board[pos.y][pos.x] && board[pos.y][pos.x]/8 == turn)
   {
      selected = 1;
      selectedPos = pos;
      newMessage.highlightSpace.pos = pos;
      newMessage.highlightSpace.color = 1;

      generateMoves(pos);

      {

         sharedGame.pushToOne(newMessage,turn);

         for (auto iter = move.begin(); iter != move.end(); iter++)
         {
            newMessage.highlightSpace.pos = *iter;
            newMessage.highlightSpace.color = 2;

            sharedGame.pushToOne(newMessage,turn);
         }

         for (auto iter = hit.begin(); iter != hit.end(); iter++)
         {
            newMessage.highlightSpace.pos = *iter;
            newMessage.highlightSpace.color = 3;

            sharedGame.pushToOne(newMessage,turn);
         }

         for (auto iter = castle.begin(); iter != castle.end(); iter++)
         {
            newMessage.highlightSpace.pos = *iter;
            newMessage.highlightSpace.color = 4;

            sharedGame.pushToOne(newMessage,turn);
         }

      }


   }
}
