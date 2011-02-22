#include <iostream>
#include <bitset>

#include <boost/thread.hpp>

#include <cstdio>

#include "chessEngine.h"
#include "messages.h"

void printBit(const std::bitset<64> &set)
{
   for (int y = 0; y <8; y++)
   {
      for (int x = 0; x <8; x++)
      {
         std::cout<<set[y *8 + x];
      }

      std::cout<<std::endl;
   }
}

bool t_chessEngine::checkCheckmate()
{
   int color = turn;

   t_myVector2 pos, square, block;
   std::bitset<64> attackingSquares;
   std::bitset<64> movingSquares;

   std::vector<t_myVector2> defendingPieces;
   std::vector<t_myVector2> spaces;

   std::set<t_myVector2> pieces;

   bool blocked = 0;

   if (turn == 0)
   {
      pieces = whitePieces;
      pos = whiteKingPos;
      defendingPieces.push_back(pos);
   }

   else
   {
      pieces = blackPieces;
      pos = blackKingPos;
      defendingPieces.push_back(pos);
   }

   std::cout<<pos<<std::endl;
   std::cout<<pieces.size()<<std::endl;

//Knight moves----------------------------------------

   square.x = pos.x + 2;
   square.y = pos.y +1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x - 2;
   square.y = pos.y +1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x + 2;
   square.y = pos.y-1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x - 2;
   square.y = pos.y-1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x + 1;
   square.y = pos.y + 2;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x - 1;
   square.y = pos.y + 2;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x + 1;
   square.y = pos.y - 2;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x - 1;
   square.y = pos.y - 2;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 3)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }


   //Rook moves-------------------------------------------------------

   square.x = pos.x;
   square.y = pos.y + 1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      spaces.push_back(square);

      if (board[square.y][square.x] != 0)
      {
         if (!blocked)
         {
            if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
            {
               for (auto iter = spaces.begin(); iter != spaces.end(); iter++)
               {
                  attackingSquares[iter->y * 8 + iter->x] = 1;
               }

               break;
            }

            else
            {
               if (board[square.y][square.x]/8 == color)
               {
                  block = square;
                  blocked = 1;
               }

               else
               {
                  break;
               }
            }
         }

         else if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
         {
            defendingPieces.push_back(block);
            break;
         }

         else
         {
            break;
         }
      }

      square.y+= +1;
   }

   spaces.clear();
   blocked = 0;

   square.x = pos.x;
   square.y = pos.y-1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      spaces.push_back(square);

      if (board[square.y][square.x] != 0)
      {
         if (!blocked)
         {
            if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
            {
               for (auto iter = spaces.begin(); iter != spaces.end(); iter++)
               {
                  attackingSquares[iter->y * 8 + iter->x] = 1;
               }

               break;
            }

            else
            {
               if (board[square.y][square.x]/8 == color)
               {
                  block = square;
                  blocked = 1;
               }

               else
               {
                  break;
               }
            }
         }

         else if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
         {
            defendingPieces.push_back(block);
            break;
         }

         else
         {
            break;
         }
      }

      square.y+=-1;
   }

   spaces.clear();
   blocked = 0;

   square.x = pos.x +1;
   square.y = pos.y;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      spaces.push_back(square);

      if (board[square.y][square.x] != 0)
      {
         if (!blocked)
         {
            if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
            {
               for (auto iter = spaces.begin(); iter != spaces.end(); iter++)
               {
                  attackingSquares[iter->y * 8 + iter->x] = 1;
               }

               break;
            }

            else
            {
               if (board[square.y][square.x]/8 == color)
               {
                  block = square;
                  blocked = 1;
               }

               else
               {
                  break;
               }
            }
         }

         else if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
         {
            defendingPieces.push_back(block);
            break;
         }

         else
         {
            break;
         }
      }

      square.x+= +1;
   }

   spaces.clear();
   blocked = 0;

   square.x = pos.x-1;
   square.y = pos.y;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      spaces.push_back(square);

      if (board[square.y][square.x] != 0)
      {
         if (!blocked)
         {
            if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
            {
               for (auto iter = spaces.begin(); iter != spaces.end(); iter++)
               {
                  attackingSquares[iter->y * 8 + iter->x] = 1;
               }

               break;
            }

            else
            {
               if (board[square.y][square.x]/8 == color)
               {
                  block = square;
                  blocked = 1;
               }

               else
               {
                  break;
               }
            }
         }

         else if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 2 || board[square.y][square.x]%8 == 6))
         {
            defendingPieces.push_back(block);
            break;
         }

         else
         {
            break;
         }
      }

      square.x+=-1;
   }

   spaces.clear();
   blocked = 0;


//Bishop moves------------------------------------------------------------

   square.x = pos.x + 1;
   square.y = pos.y + 1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      spaces.push_back(square);

      if (board[square.y][square.x] != 0)
      {
         if (!blocked)
         {
            if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
            {
               for (auto iter = spaces.begin(); iter != spaces.end(); iter++)
               {
                  attackingSquares[iter->y * 8 + iter->x] = 1;
               }

               break;
            }

            else
            {
               if (board[square.y][square.x]/8 == color)
               {
                  block = square;
                  blocked = 1;
               }

               else
               {
                  break;
               }
            }
         }

         else if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
         {
            defendingPieces.push_back(block);
            break;
         }

         else
         {
            break;
         }
      }

      square.x+= 1;
      square.y+= 1;
   }

   spaces.clear();
   blocked = 0;

   square.x = pos.x - 1;
   square.y = pos.y + 1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      spaces.push_back(square);

      if (board[square.y][square.x] != 0)
      {
         if (!blocked)
         {
            if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
            {
               for (auto iter = spaces.begin(); iter != spaces.end(); iter++)
               {
                  attackingSquares[iter->y * 8 + iter->x] = 1;
               }

               break;
            }

            else
            {
               if (board[square.y][square.x]/8 == color)
               {
                  block = square;
                  blocked = 1;
               }

               else
               {
                  break;
               }
            }
         }

         else if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
         {
            defendingPieces.push_back(block);
            break;
         }

         else
         {
            break;
         }
      }

      square.x+= -1;
      square.y+= 1;
   }

   spaces.clear();
   blocked = 0;

   square.x = pos.x +1;
   square.y = pos.y -1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      spaces.push_back(square);

      if (board[square.y][square.x] != 0)
      {
         if (!blocked)
         {
            if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
            {
               for (auto iter = spaces.begin(); iter != spaces.end(); iter++)
               {
                  attackingSquares[iter->y * 8 + iter->x] = 1;
               }

               break;
            }

            else
            {
               if (board[square.y][square.x]/8 == color)
               {
                  block = square;
                  blocked = 1;
               }

               else
               {
                  break;
               }
            }
         }

         else if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
         {
            defendingPieces.push_back(block);
            break;
         }

         else
         {
            break;
         }
      }

      square.x+= +1;
      square.y+= -1;
   }

   spaces.clear();
   blocked = 0;

   square.x = pos.x-1;
   square.y = pos.y -1;

   while (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      spaces.push_back(square);

      if (board[square.y][square.x] != 0)
      {
         if (!blocked)
         {
            if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
            {
               for (auto iter = spaces.begin(); iter != spaces.end(); iter++)
               {
                  attackingSquares[iter->y * 8 + iter->x] = 1;
               }

               break;
            }

            else
            {
               if (board[square.y][square.x]/8 == color)
               {
                  block = square;
                  blocked = 1;
               }

               else
               {
                  break;
               }
            }
         }

         else if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 4 || board[square.y][square.x]%8 == 6))
         {
            defendingPieces.push_back(block);
            break;
         }

         else
         {
            break;
         }
      }

      square.x+=-1;
      square.y+=-1;
   }

   spaces.clear();
   blocked = 0;


   //Pawn moves---------------------------------------------------------------------
   square.x = pos.x + 1;
   square.y = pos.y -1 + 2 * color;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {

      if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 1 || board[square.y][square.x]%8 == 5))
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x - 1;
   square.y = pos.y -1 + 2 * color;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && (board[square.y][square.x]%8 == 1 || board[square.y][square.x]%8 == 5))
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }


   //King moves-----------------------------------------------------------------------

   square.x = pos.x + 1;
   square.y = pos.y +1 + -2 * color;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {

      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x - 1;
   square.y = pos.y +1 + -2 * turn;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x + 1;
   square.y = pos.y;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {

      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x - 1;
   square.y = pos.y;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x;
   square.y = pos.y +1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {

      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }

   square.x = pos.x;
   square.y = pos.y -1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
   {
      if (board[square.y][square.x]/8 != color && board[square.y][square.x]%8 == 5)
      {
         attackingSquares[square.y * 8 + square.x] = 1;
      }
   }


   if (attackingSquares.none())
   {
      std::cout<<"No one is attacking me"<<std::endl;
      return 0;
   }

   else
   {
      std::cout<<"I am being attacked"<<std::endl;
      printBit(attackingSquares);
      std::cout<<std::endl;
   }

   for (auto iter = pieces.begin(); iter != pieces.end(); iter++)
   {
      if (std::find(defendingPieces.begin(), defendingPieces.end(), *iter) == defendingPieces.end())
      {
         std::cout<<*iter<<" is moving\n";
         addPieceMoves(*iter,movingSquares);
      }

      else
      {
         std::cout<<*iter<<" is blocked\n";
      }
   }

   printBit(movingSquares);
   std::cout<<std::endl;

   attackingSquares &= movingSquares;

   if (attackingSquares.any())
   {
      std::cout<<"There is a move I can do"<<std::endl;
      printBit(attackingSquares);
      return 0;
   }



   square.x = pos.x - 1;
   square.y = pos.y +1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)

      if ((board[square.y][square.x]/8 != color || board[square.y][square.x] == 0) && checkCheck(square,pos) == 0)
      {
         std::cout<<"I can move the king"<<std::endl;
         std::cout<<square<<std::endl;
         return 0;
      }

   square.x = pos.x + 1;
   square.y = pos.y - 1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      if ((board[square.y][square.x]/8 != color || board[square.y][square.x] == 0) && checkCheck(square,pos) == 0)
      {
         std::cout<<"I can move the king"<<std::endl;
         std::cout<<square<<std::endl;
         return 0;
      }

   square.x = pos.x - 1;
   square.y = pos.y - 1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      if ((board[square.y][square.x]/8 != color || board[square.y][square.x] == 0) && checkCheck(square,pos) == 0)
      {
         std::cout<<"I can move the king3"<<std::endl;
         std::cout<<square<<std::endl;
         return 0;
      }

   square.x = pos.x + 1;
   square.y = pos.y;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      if ((board[square.y][square.x]/8 != color || board[square.y][square.x] == 0) && checkCheck(square,pos) == 0)
      {
         std::cout<<"I can move the king"<<std::endl;
         std::cout<<square<<std::endl;
         return 0;
      }

   square.x = pos.x - 1;
   square.y = pos.y;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      if ((board[square.y][square.x]/8 != color || board[square.y][square.x] == 0) && checkCheck(square,pos) == 0)
      {
         std::cout<<"I can move the king"<<std::endl;
         std::cout<<square<<std::endl;
         return 0;
      }

   square.x = pos.x;
   square.y = pos.y +1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      if ((board[square.y][square.x]/8 != color || board[square.y][square.x] == 0) && checkCheck(square,pos) == 0)
      {
         std::cout<<"I can move the king"<<std::endl;
         std::cout<<square - pos<<std::endl;
         return 0;
      }

   square.x = pos.x;
   square.y = pos.y -1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      if ((board[square.y][square.x]/8 != color || board[square.y][square.x] == 0) && checkCheck(square,pos) == 0)
      {
         std::cout<<"I can move the king"<<std::endl;
         std::cout<<square - pos<<std::endl;
         return 0;
      }

   square.x = pos.x + 1;
   square.y = pos.y + 1;

   if (square.x >= 0 && square.x <= 7 && square.y >=0 && square.y <= 7)
      if ((board[square.y][square.x]/8 != color || board[square.y][square.x] == 0) && checkCheck(square,pos) == 0)
      {
         std::cout<<"I can move the king2"<<std::endl;
         std::cout<<square - pos<<std::endl;
         return 0;
      }

   return 1;
}


