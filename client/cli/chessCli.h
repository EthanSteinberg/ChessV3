#ifndef CHESS_CLI_H_INCLUDED
#define CHESS_CLI_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <bitset>

#include "myvector2.h"

#include "engine/chessEngine.h"


class t_sharedData;
class t_message;

class t_chessCli : boost::noncopyable
{
public:
   t_chessCli(t_sharedData &theSharedData);

   void run();

   ~t_chessCli()
   {
   }

private:
   bool processMessageSingle(const t_message &message);
   bool processMessageConnected(const t_message &message);

   t_sharedData &sharedData;

   bool connected;
   enum {NOTHING, PLAYING_ONE, PLAYING_TWO, PLAYING_NET} status;

   t_chessEngine chessEngine;

   bool uciTurn;
   std::string uciLocation;

   int in[2];
   FILE *blah;
};

#endif
