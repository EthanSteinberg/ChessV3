#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessCli.h"
#include "messages.h"

void t_chessCli::moveMove(t_myVector2 pos)
{
   t_message newMessage;
   newMessage.id = HIGHLIGHT_SPACE;

   if (checkCheck(pos,selectedPos))
   {
      std::cout<<"I am in check"<<std::endl;
      return;
   }

   if (turn == 0)
   {
      whitePieces.erase(selectedPos);
      whitePieces.insert(pos);
   }

   else
   {
      blackPieces.erase(selectedPos);
      blackPieces.insert(pos);
   }

   removeCastle(pos,selectedPos);

   selected = 0;
   newMessage.highlightSpace.pos = selectedPos;
   newMessage.highlightSpace.color = 0;

   {

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

      newMessage.id = MOVE_PIECE;
      newMessage.movePiece.pos = pos;
      newMessage.movePiece.oldPos = selectedPos;

   sharedGame.pushToBoth(newMessage);
   }

   move.clear();
   hit.clear();
   castle.clear();

   board[pos.y][pos.x] = board[selectedPos.y][selectedPos.x];
   board[selectedPos.y][selectedPos.x] = 0;

   turn = !turn;

   if (checkCheckmate())
   {
      std::cout<<"I win"<<std::endl;
   }

}


void t_chessCli::attackMove(t_myVector2 pos)
{
   t_message newMessage;
   newMessage.id = HIGHLIGHT_SPACE;

   if (checkCheck(pos,selectedPos))
   {
      std::cout<<"I am in check"<<std::endl;
      return;
   }

   if (turn == 0)
   {
      whitePieces.erase(selectedPos);
      whitePieces.insert(pos);

      blackPieces.erase(pos);
   }

   else
   {
      blackPieces.erase(selectedPos);
      blackPieces.insert(pos);

      whitePieces.erase(pos);
   }

   removeCastle(pos,selectedPos);

   selected = 0;
   newMessage.highlightSpace.pos = selectedPos;
   newMessage.highlightSpace.color = 0;

   {

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

      newMessage.id = CAPTURE_PIECE;
      newMessage.movePiece.pos = pos;
      newMessage.movePiece.oldPos = selectedPos;

   sharedGame.pushToBoth(newMessage);
   }

   move.clear();
   hit.clear();
   castle.clear();

   board[pos.y][pos.x] = board[selectedPos.y][selectedPos.x];
   board[selectedPos.y][selectedPos.x] = 0;

   turn = !turn;

   if (checkCheckmate())
   {
      std::cout<<"I win"<<std::endl;
   }
}
void t_chessCli::castleMove(t_myVector2 pos)
{
   t_message newMessage;
   newMessage.id = HIGHLIGHT_SPACE;

   if (checkCheck(pos,selectedPos))
   {
      std::cout<<"I am in check"<<std::endl;
      return;
   }

   if (turn == 0)
   {
      whitePieces.erase(selectedPos);
      whitePieces.insert(pos);
   }

   else
   {
      blackPieces.erase(selectedPos);
      blackPieces.insert(pos);
   }

   removeCastle(pos,selectedPos);

   selected = 0;
   newMessage.highlightSpace.pos = selectedPos;
   newMessage.highlightSpace.color = 0;

   {

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

      newMessage.id = MOVE_PIECE;
      newMessage.movePiece.pos = pos;
      newMessage.movePiece.oldPos = selectedPos;

   sharedGame.pushToBoth(newMessage);

      if (pos.x == 2) //left castle
      {
         newMessage.movePiece.pos.x = 3;
         newMessage.movePiece.oldPos.x = 0;
      }

      else
      {
         newMessage.movePiece.pos.x = 5;
         newMessage.movePiece.oldPos.x = 7;
      }

   sharedGame.pushToBoth(newMessage);
   }

   move.clear();
   hit.clear();
   castle.clear();

   board[pos.y][pos.x] = board[selectedPos.y][selectedPos.x];
   board[selectedPos.y][selectedPos.x] = 0;

   if (pos.x == 2) //left
   {
      pos.x = 3;
      selectedPos.x = 0;

      board[pos.y][3] = board[selectedPos.y][0];
      board[selectedPos.y][0] = 0;
   }

   else
   {
      pos.x = 5;
      selectedPos.x = 7;

      board[pos.y][5] = board[selectedPos.y][7];
      board[selectedPos.y][7] = 0;
   }

   if (turn == 0)
   {
      whitePieces.erase(selectedPos);
      whitePieces.insert(pos);
   }

   else
   {
      blackPieces.erase(selectedPos);
      blackPieces.insert(pos);
   }

   turn = !turn;


   if (checkCheckmate())
   {
      std::cout<<"I win"<<std::endl;
   }

}
