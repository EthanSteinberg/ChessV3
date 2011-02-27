#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessEngine.h"
#include "messages.h"

std::vector<t_message> t_chessEngine::boardClickedSingle(const t_message &message)
{
   std::vector<t_message> buffer;

   if (inPawnPromotion)
   {
      if (message.id != RECIEVE_PAWN_PROMOTE)
         return buffer;

      int type = message.recievePawnPromote.type;
      finishPromote(type,buffer);
      std::cout<<"I am in pawn promotion, ID: "<<type<<" and location "<<pawnPos<<std::endl; 
   }

   else
   {

   t_myVector2 pos = message.boardClicked.pos;
   std::cout<<"It was clicked at "<<pos<<std::endl;

   t_message newMessage;
   newMessage.id = HIGHLIGHT_SPACE;


    if (selected)
   {
      if (pos == selectedPos)
      {
         clearHighlights(buffer);
      }

      else if (std::find(move.begin(), move.end(), pos) != move.end())
      {
         moveMove(pos,buffer);
      }

      else if (std::find(hit.begin(), hit.end(), pos) != hit.end())
      {
         attackMove(pos,buffer);
      }

      else if (std::find(castle.begin(), castle.end(), pos) != castle.end())
      {
         castleMove(pos,buffer);
      }

      else if (std::find(pawnPromote.begin(), pawnPromote.end(), pos) != pawnPromote.end())
      {
         promoteMove(pos,buffer);
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
         buffer.push_back(newMessage);

         for (auto iter = move.begin(); iter != move.end(); iter++)
         {
            newMessage.highlightSpace.pos = *iter;
            newMessage.highlightSpace.color = 2;

            buffer.push_back(newMessage);
         }

         for (auto iter = hit.begin(); iter != hit.end(); iter++)
         {
            newMessage.highlightSpace.pos = *iter;
            newMessage.highlightSpace.color = 3;

            buffer.push_back(newMessage);
         }

         for (auto iter = castle.begin(); iter != castle.end(); iter++)
         {
            newMessage.highlightSpace.pos = *iter;
            newMessage.highlightSpace.color = 4;

            buffer.push_back(newMessage);
         }

         for (auto iter = pawnPromote.begin(); iter != pawnPromote.end(); iter++)
         {
            newMessage.highlightSpace.pos = *iter;
            newMessage.highlightSpace.color = 5;

            buffer.push_back(newMessage);
         }
      }


   }
   }

   return buffer;
}

bool t_chessEngine::getTurn()
{
   return turn;
}
