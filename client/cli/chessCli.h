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
   bool playing;

   t_chessEngine chessEngine;
};

#endif
