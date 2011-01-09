#include <iostream>
#include <bitset>

#include <boost/thread.hpp>

#include <cstdio>

#include "chessCli.h"
#include "../messages.h"

bool t_chessCli::checkCheckmate()
{
   t_myVector2 pos;
   std::bitset<64> attackingSquares;
   std::bitset<64> defendingPieces;
   std::bitset<64> movingSquares;

   if (turn == 0)
   {
      pos = whiteKingPos;
   }

   else
   {
      pos = blackKingPos;
   }

   

   return 0;
}
