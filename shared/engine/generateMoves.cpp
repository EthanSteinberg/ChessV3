#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>

#include "chessEngine.h"
#include "messages.h"

void t_chessEngine::generateMoves(const t_myVector2 &pos)
{
   int piece = board[pos.y][pos.x];
   int color = piece/8;
   int type = piece%8;

   printf("\nPiece: %d Color: %d Type: %d\n",piece,color,type);

   t_myVector2 square;

   if (type == 1) //pawn
   {
      bool forwardBlocked = 1;
      square.x = pos.x;
      square.y = pos.y -1 + 2 * color;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {
         if (board[square.y][square.x] == 0)
         {
            if (pos.y == 1 + 5 * color)
            {
               pawnPromote.push_back(square);
            }

            else
            {
               forwardBlocked = 0;
               move.push_back(square);
            }
         }
      }

      if (pos.y == 6 - 5 * color && !forwardBlocked)
      {
         square.x = pos.x;
         square.y = pos.y -2 + 4 * color;

         if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
         {

            if (board[square.y][square.x] == 0)
            {
               move.push_back(square);
            }
         }
      }


      square.x = pos.x + 1;
      square.y = pos.y -1 + 2 * color;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x]/8 != color && board[square.y][square.x] != 0)
         {
            if (pos.y == 1 + 5 * color)
            {
               pawnPromote.push_back(square);
            }

            else
            {
               hit.push_back(square);
            }
         }
      }

      square.x = pos.x - 1;
      square.y = pos.y -1 + 2 * color;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {
         if (board[square.y][square.x]/8 != color && board[square.y][square.x] != 0)
         {
            if (pos.y == 1 + 5 * color)
            {
               pawnPromote.push_back(square);
            }

            else
            {
               hit.push_back(square);
            }
         }
      }
   }

   if (type == 2 || type == 6) //rook
   {
      square.x = pos.x;
      square.y = pos.y + 1;

      while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {
         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
            break;
         }

         else
         {
            break;
         }

         square.y+= +1;
      }

      square.x = pos.x;
      square.y = pos.y-1;

      while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {
         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
            break;
         }

         else
         {
            break;
         }

         square.y+=-1;
      }

      square.x = pos.x +1;
      square.y = pos.y;

      while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {
         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
            break;
         }

         else
         {
            break;
         }

         square.x+= +1;
      }

      square.x = pos.x-1;
      square.y = pos.y;

      while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {
         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
            break;
         }

         else
         {
            break;
         }

         square.x+=-1;
      }
   }


   if (type == 3) // knight
   {
      square.x = pos.x + 2;
      square.y = pos.y +1;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x - 2;
      square.y = pos.y +1;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x + 2;
      square.y = pos.y-1;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x - 2;
      square.y = pos.y-1;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x + 1;
      square.y = pos.y + 2;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x - 1;
      square.y = pos.y + 2;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x + 1;
      square.y = pos.y - 2;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x - 1;
      square.y = pos.y - 2;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }
   }

   if (type == 4 || type == 6) //bishop
   {
      square.x = pos.x + 1;
      square.y = pos.y + 1;

      while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {
         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
            break;
         }

         else
         {
            break;
         }

         square.x+= 1;
         square.y+= 1;
      }

      square.x = pos.x - 1;
      square.y = pos.y + 1;

      while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {
         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
            break;
         }

         else
         {
            break;
         }

         square.x+= -1;
         square.y+= 1;
      }

      square.x = pos.x +1;
      square.y = pos.y -1;

      while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {
         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
            break;
         }

         else
         {
            break;
         }

         square.x+= +1;
         square.y+= -1;
      }

      square.x = pos.x-1;
      square.y = pos.y -1;

      while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {
         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
            break;
         }

         else
         {
            break;
         }

         square.x+=-1;
         square.y+=-1;
      }
   }

   if (type == 5) //king
   {
      if (pos.x == 4 && pos.y == 7 -color *7)
      {
         std::cout<<"A king is being evaluated for castling"<<std::endl;

         if (color == 0)
         {
            if (whiteCanCastleLeft && !board[pos.y][pos.x -1] && !board[pos.y][pos.x -2] && !board[pos.y][pos.x -3])
            {
               std::cout<<"Said king can castle left"<<std::endl;
               square.x = pos.x -2;
               square.y = pos.y;

               castle.push_back(square);
            }

            if (whiteCanCastleRight && !board[pos.y][pos.x +1] && !board[pos.y][pos.x +2])
            {
               std::cout<<"Said king can castle right"<<std::endl;
               square.x = pos.x +2;
               square.y = pos.y;

               castle.push_back(square);
            }
         }

         else
         {
            if (blackCanCastleLeft && !board[pos.y][pos.x -1] && !board[pos.y][pos.x -2] && !board[pos.y][pos.x -3])
            {
               std::cout<<"Said king can castle left"<<std::endl;
               square.x = pos.x -2;
               square.y = pos.y;

               castle.push_back(square);
            }

            if (blackCanCastleRight && !board[pos.y][pos.x +1] && !board[pos.y][pos.x +2])
            {
               std::cout<<"Said king can castle right"<<std::endl;
               square.x = pos.x +2;
               square.y = pos.y;

               castle.push_back(square);
            }
         }
      }


      square.x = pos.x + 1;
      square.y = pos.y;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x - 1;
      square.y = pos.y;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x + 1;
      square.y = pos.y + 1;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x - 1;
      square.y = pos.y + 1;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x + 1;
      square.y = pos.y - 1;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x - 1;
      square.y = pos.y - 1;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x;
      square.y = pos.y + 1;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }

      square.x = pos.x;
      square.y = pos.y - 1;

      if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      {

         if (board[square.y][square.x] == 0)
         {
            move.push_back(square);
         }

         else if (board[square.y][square.x]/8 != color)
         {
            hit.push_back(square);
         }
      }
   }

}
