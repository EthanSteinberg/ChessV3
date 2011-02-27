#include "chessEngine.h"
#include "messages.h"

t_message t_chessEngine::insertMove(const t_myVector2 &oldPos, const t_myVector2 &newPos)
{

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

   board[newPos.y][newPos.x] = board[oldPos.y][oldPos.x];
   board[oldPos.y][oldPos.x] = 0;

   turn = !turn;

   return newMessage;
}
