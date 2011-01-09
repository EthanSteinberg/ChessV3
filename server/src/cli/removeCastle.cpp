#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>

#include "chessCli.h"
#include "../messages.h"

void t_chessCli::removeCastle(const t_myVector2 &newPos, const t_myVector2 &pos)
{
   int piece = board[pos.y][pos.x];
   int color = piece/8;
   int type = piece%8;

   std::cout<<"I am testing the removal of a castle"<<std::endl;

   if (pos.y == 7 + -7*color)
   {
      if (type == 5)
      {
         if (color == 0)
         {
            whiteCanCastleRight = 0;
            whiteCanCastleLeft = 0;

            whiteKingPos = newPos;
         }

         else
         {
            blackCanCastleRight = 0;
            blackCanCastleLeft = 0;

            blackKingPos = newPos;
         }

         std::cout<<"A king has been moved"<<std::endl;
      }

      if (type == 2)
      {
         if (color == 0)
         {
            if (pos.x == 0)
            {
               whiteCanCastleLeft = 0;
               std::cout<<"A rook has been moved"<<std::endl;
            }

            else if (pos.x == 7)
            {
               whiteCanCastleRight = 0;
               std::cout<<"A rook has been moved"<<std::endl;
            }
         }

         else
         {
            if (pos.x == 0)
            {
               blackCanCastleLeft = 0;
               std::cout<<"A rook has been moved"<<std::endl;
            }

            else if (pos.x == 7)
            {
               blackCanCastleRight = 0;
               std::cout<<"A rook has been moved"<<std::endl;
            }
         }
      }
   }
}

