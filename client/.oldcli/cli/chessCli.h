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
   void generateMoves(const t_myVector2 &pos);
   void removeCastle(const t_myVector2 &pos, const t_myVector2 &oldPos);

   bool checkCheck(const t_myVector2 &pos, const t_myVector2 &oldPos);
   bool checkCheckmate();

   void addPieceMoves(const t_myVector2 &pos, std::bitset<64> &defendingPieces);

   bool processMessageSingle(const t_message &message);
   bool processMessageConnected(const t_message &message);
   void boardClickedSingle(const t_message &message);


   void castleMove(t_myVector2 pos);
   void attackMove( t_myVector2 pos);
   void moveMove(t_myVector2 pos);

   std::vector<t_myVector2> move;
   std::vector<t_myVector2> hit;
   std::vector<t_myVector2> castle;

   t_sharedData &sharedData;

   char board[8][8];

   t_myVector2 selectedPos;
   bool selected;

   bool whiteCanCastleLeft;
   bool whiteCanCastleRight;

   bool blackCanCastleLeft;
   bool blackCanCastleRight;

   bool turn;

   t_myVector2 whiteKingPos;
   t_myVector2 blackKingPos;

   std::set<t_myVector2> whitePieces;
   std::set<t_myVector2> blackPieces;

   bool connected;

   t_chessEngine chessEngine;
};

#endif
