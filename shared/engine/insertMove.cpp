#include "chessEngine.h"
#include "messages.h"
#include <iostream>

std::vector<t_message> t_chessEngine::insertMove(const t_myVector2 &oldPos, const t_myVector2 &newPos)
{

   t_myVector2 pos = newPos;

   std::vector<t_message> buffer;
   t_message newMessage;

   t_myVector2 kingPos;

   if (turn == 0)
   {
      kingPos = whiteKingPos;
   }

   else
   {
      kingPos = blackKingPos;
   }



   if (board[pos.y][pos.x] != 0)// if it is a capture, not a move
   {
      newMessage.id = CAPTURE_PIECE;
      newMessage.movePiece.pos = pos;
      newMessage.movePiece.oldPos = oldPos;

      if (turn == 0)
      {
         whitePieces.erase(oldPos);
         whitePieces.insert(pos);

         blackPieces.erase(pos);
      }

      else
      {
         blackPieces.erase(oldPos);
         blackPieces.insert(pos);

         whitePieces.erase(pos);
      }
   }

   else
   {
      newMessage.id = MOVE_PIECE;
      newMessage.movePiece.pos = pos;
      newMessage.movePiece.oldPos = oldPos;

      if (turn == 0)
      {
         whitePieces.erase(oldPos);
         whitePieces.insert(pos);
      }

      else
      {
         blackPieces.erase(oldPos);
         blackPieces.insert(pos);
      }
   }

   buffer.push_back(newMessage);

   board[pos.y][pos.x] = board[oldPos.y][oldPos.x];
   board[oldPos.y][oldPos.x] = 0;

   if (oldPos.x == 4 && (oldPos.y == 0 || oldPos.y == 7) && kingPos == oldPos && (pos.y == 0 || pos.y == 7))
   {
      newMessage.id = MOVE_PIECE;
      newMessage.movePiece.pos = pos;
      newMessage.movePiece.oldPos = oldPos;

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

      buffer.push_back(newMessage);

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
   }

   if (enPessantPossible)
   {
      enPessantPossible--;
   }

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
