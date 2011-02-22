#include <iostream>

#include <boost/thread.hpp>
#include <boost/optional.hpp>

#include <cstdio>

#include "chessEngine.h"
#include "messages.h"

boost::optional<t_myVector2> t_chessEngine::checkCheck(const t_myVector2 &posTo, const t_myVector2 &oldPos)
{
   int temp = board[posTo.y][posTo.x];
   board[posTo.y][posTo.x] = board[oldPos.y][oldPos.x];
   board[oldPos.y][oldPos.x] = 0;


   t_myVector2 tempKing;
   if (board[posTo.y][posTo.x] == 5)
   {
      tempKing = whiteKingPos;
      whiteKingPos = posTo;
   }

   else if (board[posTo.y][posTo.x] == 13)
   {
      tempKing = blackKingPos;
      blackKingPos = posTo;
   }




   t_myVector2 pos,square;
   int color = turn;

   if (turn == 0)
   {
      pos = whiteKingPos;
   }

   else
   {
      pos = blackKingPos;
   }

//Knight moves----------------------------------------

   square.x = pos.x + 2;
   square.y = pos.y +1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         goto bad;
      }
   }

   square.x = pos.x - 2;
   square.y = pos.y +1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         goto bad;
      }
   }

   square.x = pos.x + 2;
   square.y = pos.y-1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         goto bad;
      }
   }

   square.x = pos.x - 2;
   square.y = pos.y-1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         goto bad;
      }
   }

   square.x = pos.x + 1;
   square.y = pos.y + 2;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         goto bad;
      }
   }

   square.x = pos.x - 1;
   square.y = pos.y + 2;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         goto bad;
      }
   }

   square.x = pos.x + 1;
   square.y = pos.y - 2;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         goto bad;
      }
   }

   square.x = pos.x - 1;
   square.y = pos.y - 2;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         goto bad;
      }
   }


   //Rook moves-------------------------------------------------------

   square.x = pos.x;
   square.y = pos.y + 1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x] != 0)
      {
         if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
         {
            goto bad;
         }

         else
         {
            break;
         }
      }

      square.y+= +1;
   }

   square.x = pos.x;
   square.y = pos.y-1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x] != 0)
      {
         if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
         {
            goto bad;
         }

         else
         {
            break;
         }
      }

      square.y+=-1;
   }

   square.x = pos.x +1;
   square.y = pos.y;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x] != 0)
      {
         if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
         {
            goto bad;
         }

         else
         {
            break;
         }
      }

      square.x+= +1;
   }

   square.x = pos.x-1;
   square.y = pos.y;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x] != 0)
      {
         if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
         {
            goto bad;
         }

         else
         {
            break;
         }
      }

      square.x+=-1;
   }


//Bishop moves------------------------------------------------------------

   square.x = pos.x + 1;
   square.y = pos.y + 1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x] != 0)
      {
         if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
         {
            goto bad;
         }

         else
         {
            break;
         }
      }

      square.x+= 1;
      square.y+= 1;
   }

   square.x = pos.x - 1;
   square.y = pos.y + 1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x] != 0)
      {
         if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
         {
            goto bad;
         }

         else
         {
            break;
         }
      }

      square.x+= -1;
      square.y+= 1;
   }

   square.x = pos.x +1;
   square.y = pos.y -1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x] != 0)
      {
         if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
         {
            goto bad;
         }

         else
         {
            break;
         }
      }

      square.x+= +1;
      square.y+= -1;
   }

   square.x = pos.x-1;
   square.y = pos.y -1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x] != 0)
      {
         if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
         {
            goto bad;
         }

         else
         {
            break;
         }
      }

      square.x+=-1;
      square.y+=-1;
   }


   //Pawn moves---------------------------------------------------------------------
   square.x = pos.x + 1;
   square.y = pos.y -1 + 2 * turn;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {

      if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 1 || board[square.y][square.x]%8 == 5))
      {
         goto bad;
      }
   }

   square.x = pos.x - 1;
   square.y = pos.y -1 + 2 * turn;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 1 || board[square.y][square.x]%8 == 5))
      {
         goto bad;
      }
   }


   //King moves-----------------------------------------------------------------------

   square.x = pos.x + 1;
   square.y = pos.y +1 + -2 * turn;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {

      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         goto bad;
      }
   }

   square.x = pos.x - 1;
   square.y = pos.y +1 + -2 * turn;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         goto bad;
      }
   }

   square.x = pos.x + 1;
   square.y = pos.y;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {

      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         goto bad;
      }
   }

   square.x = pos.x - 1;
   square.y = pos.y;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         goto bad;
      }
   }

   square.x = pos.x;
   square.y = pos.y +1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {

      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         goto bad;
      }
   }

   square.x = pos.x;
   square.y = pos.y -1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         goto bad;
      }
   }

   //Clean up after-----------------------------------------------------------------------------------------------

   if (board[posTo.y][posTo.x] == 5)
   {
      whiteKingPos = tempKing;
   }

   else if (board[posTo.y][posTo.x] == 13)
   {
      blackKingPos = tempKing;
   }


   board[oldPos.y][oldPos.x] = board[posTo.y][posTo.x];
   board[posTo.y][posTo.x] = temp;
   return boost::optional<t_myVector2>();

bad:

   if (board[posTo.y][posTo.x] == 5)
   {
      whiteKingPos = tempKing;
   }

   else if (board[posTo.y][posTo.x] == 13)
   {
      blackKingPos = tempKing;
   }

   board[oldPos.y][oldPos.x] = board[posTo.y][posTo.x];
   board[posTo.y][posTo.x] = temp;
   return square;

}

