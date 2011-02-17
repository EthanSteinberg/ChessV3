#include "chessEngine.h"

#include <iostream>

t_chessEngine::t_chessEngine()
{
   std::cout<<"Engine is ready to go"<<std::endl;
}

void t_chessEngine::reset() 
{
   std::cout<<"Hello world"<<std::endl;

   selected = 0;

   board =
   {
      {10, 11, 12, 14, 13, 12, 11, 10},
      { 9,  9,  9,  9,  9,  9,  9,  9},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 1,  1,  1,  1,  1,  1,  1,  1},
      { 2,  3,  4,  6,  5,  4,  3,  2}
   };

   whiteCanCastleLeft = 1;
   whiteCanCastleRight = 1;

   blackCanCastleLeft = 1;
   blackCanCastleRight = 1;

   turn = 0;

   whiteKingPos.x = 4;
   blackKingPos.x = 4;

   whiteKingPos.y = 7;
   blackKingPos.y = 0;


   t_myVector2 pos;

   for (int y = 6; y < 8; y++)
   {
      pos.y = y;

      for (int x = 0; x<8; x++)
      {
         pos.x = x;
         whitePieces.insert(pos);
      }
   }

   for (int y = 0; y < 2; y++)
   {
      pos.y = y;

      for (int x = 0; x<8; x++)
      {
         pos.x = x;
         blackPieces.insert(pos);
      }
   }
}
