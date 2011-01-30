#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED

#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>

#include "myvector2.h"

#include <string>

enum {QUIT_MESSAGE, BOARD_CLICKED, HIGHLIGHT_SPACE, MOVE_PIECE, CAPTURE_PIECE, JOIN_SERVER};

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

struct t_message
{
   int id;

   union 
   {
      t_boardClicked boardClicked;
      t_highlightSpace highlightSpace;
      t_movePiece movePiece;
      t_joinServer joinServer;
   };

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

#endif
