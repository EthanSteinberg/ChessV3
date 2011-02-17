#ifndef CHESS_GAME_H_INCLUDED
#define CHESS_GAME_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <bitset>

#include "myvector2.h"

#include "engine/chessEngine.h"


class t_sharedGame;
class t_message;

class t_chessGame : boost::noncopyable
{
public:
   t_chessGame(t_sharedGame &theSharedGame);

   void run();

   ~t_chessGame()
   {
   }

private:
   bool processMessageServer(const t_message &message);

   t_sharedGame &sharedGame;

   t_chessEngine chessEngine;
};

#endif
