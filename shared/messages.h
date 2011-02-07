#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED

#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>

#include "myvector2.h"
//#include "myDataBase.h"
#include <vector>

#include <string>

enum {QUIT_MESSAGE, BOARD_CLICKED, HIGHLIGHT_SPACE, MOVE_PIECE, CAPTURE_PIECE, JOIN_SERVER, REFRESH_CONNECTION, WANT_REFRESH_CONNECTION, CONNECTION_SUCCESS, CONNECTION_BAD_NAME, CONNECTION_NO_SERVER, CONNECTION_FAILED};

struct t_boardClicked
{
   t_myVector2 pos;
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

#endif
