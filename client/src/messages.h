#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED

#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>

#include "myvector2.h"

enum {QUIT_MESSAGE, BOARD_CLICKED, HIGHLIGHT_SPACE, MOVE_PIECE};


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

struct t_message
{
   int id;

   union 
   {
      t_boardClicked boardClicked;
      t_highlightSpace highlightSpace;
      t_movePiece movePiece;
   };

};

typedef boost::circular_buffer<t_message> t_messageBuffer;

struct t_sharedData
{
   t_sharedData() : clientBuffer(10), gameBuffer(10)
   {}

   boost::mutex clientMutex;
   boost::mutex gameMutex;

   boost::condition_variable clientCondition;
   boost::condition_variable gameCondition;

   t_messageBuffer clientBuffer;
   t_messageBuffer gameBuffer;
};

#endif
