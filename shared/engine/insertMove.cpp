#include "chessEngine.h"
#include "messages.h"
#include <iostream>

std::vector<t_message> t_chessEngine::insertMove(const t_myVector2 &oldPos, const t_myVector2 &newPos)
{

   std::vector<t_message> buffer;
   t_message newMessage;
   if (board[newPos.y][newPos.x] != 0)// if it is a capture, not a move
   {
      newMessage.id = CAPTURE_PIECE;
      newMessage.movePiece.pos = newPos;
      newMessage.movePiece.oldPos = oldPos;
   }

   else
   {
      newMessage.id = MOVE_PIECE;
      newMessage.movePiece.pos = newPos;
      newMessage.movePiece.oldPos = oldPos;
   }
   buffer.push_back(newMessage);

   board[newPos.y][newPos.x] = board[oldPos.y][oldPos.x];
   board[oldPos.y][oldPos.x] = 0;

   if (enPessantPossible)
      enPessantPossible--;

   turn = !turn;

   if (checkCheckmate())
   {
      newMessage.id = CHECK_MATE;
      newMessage.checkMate.winner = !turn;
      buffer.push_back(newMessage);
      std::cout<<"I win"<<std::endl;
   }


   return buffer;
}
