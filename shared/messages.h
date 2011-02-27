#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED

#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>

#include "myvector2.h"
//#include "myDataBase.h"
#include <vector>

#include <string>

struct t_connectionData;
struct t_sharedGame;

enum {QUIT_MESSAGE, BOARD_CLICKED, HIGHLIGHT_SPACE, MOVE_PIECE, CAPTURE_PIECE, IN_CHECK, CHECK_MATE, 
   JOIN_SERVER, REFRESH_CONNECTION, WANT_REFRESH_CONNECTION, CONNECTION_SUCCESS, CONNECTION_BAD_NAME, CONNECTION_NO_SERVER, CONNECTION_FAILED, DISCONNECT_MESSAGE, 
   WANT_TO_PLAY_WITH, PLAY_REQUEST, PLAY_RESPONSE, PLAY_ACCEPTED, PLAY_REJECTED, PASS_GAME, 
   WANT_TO_RESET_BOARD, RESET_WARNING_SINGLE, RESET_WARNING_CONNECTED, RESET_PAST_WARNING, RESET_GUI, RESET_NET, SET_GUI, NEW_GAME_TWO, NEW_GAME_ONE, 
   PRESSED_BOARD_NOT_PLAYING,
   SET_UCI_TURN, NEW_UCI_LOCATION, UCI_RESPONSE,
   SHOW_PAWN_PROMOTE, RECIEVE_PAWN_PROMOTE, CHANGE_ICON};

struct t_uciResponse
{
   char response[40];
};

struct t_playAccepted
{
   bool side;
};

struct t_changeIcon
{
   int type;
   t_myVector2 pawnPos;
};

struct t_showPawnPromote
{
   bool color;
};

struct t_recievePawnPromote
{
   int type;
   int turn;
};

struct t_uciTurn
{
   bool turn;
};

struct t_uciLocation
{
   char place[40];
};

struct t_checkMate
{
   bool winner;
};

struct t_inCheck
{
   t_myVector2 attackingPiece;
};

struct t_boardClicked
{
   t_myVector2 pos;
   int turn;
};

struct t_highlightSpace
{
   t_myVector2 pos;
   int color;
};

struct t_movePiece
{
   t_myVector2 pos;
   t_myVector2 oldPos;
};

struct t_joinServer
{
   char name[20];
   char address[20];
};

struct t_dataPacket
{
   char name[20];
   int wins;
   int losses;
   int status;
};

struct t_refreshConnection
{
   char server[20];
};

struct t_wantToPlayWith
{
   char name[20];
};

struct t_playResponse
{
   char name[20];
   bool response;
   bool side;
};

struct t_playRequest
{
   char name[20];
};

struct t_gamePass
{
   boost::shared_ptr<t_sharedGame> *sharedGame;
   uint8_t side;
};

struct t_message
{
   int id;

   union
   {
      t_boardClicked boardClicked;
      t_highlightSpace highlightSpace;
      t_movePiece movePiece;
      t_joinServer joinServer;
      t_refreshConnection refreshConnection;
      t_wantToPlayWith wantToPlayWith;
      t_playResponse playResponse;
      t_playRequest playRequest;
      t_gamePass gamePass;
      t_inCheck inCheck;
      t_checkMate checkMate;
      t_uciTurn   uciTurn;
      t_uciLocation uciLocation;
      t_showPawnPromote showPawnPromote;
      t_recievePawnPromote recievePawnPromote;
      t_changeIcon   changeIcon;
      t_playAccepted playAccepted;
      t_uciResponse uciResponse;
   };

   std::vector<t_dataPacket> dataPackets;

};

typedef boost::circular_buffer<t_message> t_messageBuffer;

struct t_sharedData
{
   t_sharedData() : clientBuffer(100), gameBuffer(100), netBuffer(100)
   {}

   boost::mutex clientMutex;
   boost::mutex gameMutex;
   boost::mutex netMutex;

   boost::condition_variable clientCondition;
   boost::condition_variable gameCondition;
   boost::condition_variable netCondition;

   t_messageBuffer clientBuffer;
   t_messageBuffer gameBuffer;
   t_messageBuffer netBuffer;
};

struct t_myDataInfo;

struct t_connectionData
{
   t_connectionData(boost::shared_ptr<t_myDataInfo> theDataInfo) : connBuffer(100), myDataInfo(theDataInfo)
   {}

   t_connectionData() : connBuffer(100)
   {}

   boost::mutex connMutex;
   t_messageBuffer connBuffer;

   boost::shared_ptr<t_myDataInfo> myDataInfo;
};

struct t_sharedGame
{
   t_sharedGame(boost::shared_ptr<t_connectionData> firstPlayer, boost::shared_ptr<t_connectionData> secondPlayer) :
      firstMutex(firstPlayer->connMutex),secondMutex(secondPlayer->connMutex),
      firstBuffer(firstPlayer->connBuffer),secondBuffer(secondPlayer->connBuffer),
      gameBuffer(100)
   {}

   boost::mutex &firstMutex;
   boost::mutex &secondMutex;
   boost::mutex gameMutex;

   boost::condition_variable gameCondition;

   t_messageBuffer &firstBuffer;
   t_messageBuffer &secondBuffer;
   t_messageBuffer gameBuffer;

   void pushToBoth(const t_message &message)
   {
      {
         boost::unique_lock<boost::mutex> lock(firstMutex);

         firstBuffer.push_front(message);
      }

      {
         boost::unique_lock<boost::mutex> lock(secondMutex);

         secondBuffer.push_front(message);
      }
   }

   void pushToOne(const t_message &message, bool turn)
   {
      if (turn == 0)
      {
         boost::unique_lock<boost::mutex> lock(firstMutex);

         firstBuffer.push_front(message);
      }

      else
      {
         boost::unique_lock<boost::mutex> lock(secondMutex);

         secondBuffer.push_front(message);
      }
   }

   void pushToGame(t_message &message, bool turn)
   {
      if (message.id == BOARD_CLICKED)
      {
      message.boardClicked.turn = turn;
      }

      else if (message.id == RECIEVE_PAWN_PROMOTE)
      {
         message.recievePawnPromote.turn = turn;
      }

      {
         boost::unique_lock<boost::mutex> lock(gameMutex);

         gameBuffer.push_front(message);
      }

      gameCondition.notify_one();
   }

};

#endif
