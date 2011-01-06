#ifndef CHESS_CLI_H_INCLUDED
#define CHESS_CLI_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>
#include <vector>

#include "../myvector2.h"

class t_sharedData;

class t_chessCli : boost::noncopyable
{
public:
   t_chessCli(t_sharedData &theSharedData);

   void run();

   ~t_chessCli()
   {
   }

private:
   void generateMoves(const t_myVector2 &pos);

   std::vector<t_myVector2> move;
   std::vector<t_myVector2> hit;

   t_sharedData &sharedData;

   char board[8][8];

   t_myVector2 selectedPos;
   bool selected;

};

#endif
