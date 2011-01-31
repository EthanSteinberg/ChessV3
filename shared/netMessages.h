#ifndef NET_MESSAGE_H_INCLUDED
#define NET_MESSAGE_H_INCLUDED

#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>

#include "myvector2.h"

enum {NET_BOARD_CLICKED = 100, NET_HIGHLIGHT_SPACE, NET_MOVE_PIECE, NET_CAPTURE_PIECE, NET_JOIN_SERVER, NET_QUIT_MESSAGE};

struct t_netBoardClicked
{
   t_myVector2 pos;
};

struct t_netHighlightSpace
{
   t_myVector2 pos;
   int color;
};

struct t_netMovePiece
{
   t_myVector2 pos;
   t_myVector2 oldPos;
};

struct t_netJoinServer
{
   char name[20];
};


struct t_netMessage
{
   int id;

   union 
   {
      t_netBoardClicked netBoardClicked;
      t_netHighlightSpace netHighlightSpace;
      t_netMovePiece netMovePiece;
      t_netJoinServer netJoinServer;
   };

};

#endif
