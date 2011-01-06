#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>

#include "chessCli.h"
#include "../messages.h"

void t_chessCli::generateMoves(const t_myVector2 &pos)
{
   int piece = board[pos.y][pos.x];
   int color = piece/8;
   int type = piece%8;

   printf("\nPiece: %d Color: %d Type: %d\n",piece,color,type);

   t_myVector2 square;
   
   if (type == 1) //pawn
   {
      square.x = pos.x;
      square.y = pos.y -1 + 2 * color;

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

   if (type == 3) // knight
   {
      square.x = pos.x + 2;
      square.y = pos.y -1 + 2 * color;

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
      square.y = pos.y -1 + 2 * color;

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
      square.y = pos.y + 1 + -2 * color;

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
      square.y = pos.y + 1 + -2 * color;

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
      square.y = pos.y -2 + 4 * color;

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
      square.y = pos.y -2 + 4 * color;

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
      square.y = pos.y + 2 + -4 * color;

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
      square.y = pos.y + 2 + -4 * color;

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
