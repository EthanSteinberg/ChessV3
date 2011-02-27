#ifndef NET_MESSAGE_H_INCLUDED
#define NET_MESSAGE_H_INCLUDED

#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>

#include "myvector2.h"

#include <cstdint>

enum {NET_BOARD_CLICKED = 100, NET_HIGHLIGHT_SPACE, NET_MOVE_PIECE, NET_CAPTURE_PIECE, NET_JOIN_SERVER, NET_QUIT_MESSAGE, NET_REFRESH_CONNECTION, NET_CONNECTION_SUCCESS, NET_CONNECTION_BAD_NAME, NET_DISCONNECT, 
   NET_WANT_TO_PLAY_WITH, NET_PLAY_REQUEST, NET_PLAY_RESPONSE, NET_PLAY_ACCEPTED, NET_PLAY_REJECTED, NET_LEAVE_GAME, NET_CHECK_MATE, NET_IN_CHECK, NET_CHANGE_ICON, NET_SHOW_PAWN_PROMOTE, NET_RECIEVE_PAWN_PROMOTE};

struct t_netPlayAccepted
{
   uint8_t side;
};

struct t_netChangeIcon
{
   uint8_t type;
   t_myVector2 pawnPos;
};

struct t_netShowPawnPromote
{
   uint8_t color;
};

struct t_netRecievePawnPromote
{
   uint8_t type;
};

struct t_netCheckMate
{
   uint8_t winner;
};

struct t_netInCheck
{
   t_myVector2 attackingPiece;
};

struct t_netBoardClicked
{
   t_myVector2 pos;
};

struct t_netHighlightSpace
{
   t_myVector2 pos;
   uint8_t color;
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

struct t_netRefreshConnection
{
   uint8_t numOfPackets;
};

struct t_netWantToPlayWith
{
   char name[20];
};

struct t_netPlayRequest
{
   char name[20];
};

struct t_netPlayResponse
{
   char name[20];
   uint8_t response;
   uint8_t side;
};

struct t_netMessage
{
   uint8_t id;

   union 
   {
      t_netBoardClicked netBoardClicked;
      t_netHighlightSpace netHighlightSpace;
      t_netMovePiece netMovePiece;
      t_netJoinServer netJoinServer;
      t_netRefreshConnection netRefreshConnection;
      t_netWantToPlayWith netWantToPlayWith;
      t_netPlayResponse netPlayResponse;
      t_netPlayRequest netPlayRequest;
      t_netInCheck netInCheck;
      t_netCheckMate netCheckMate;
      t_netChangeIcon netChangeIcon;
      t_netShowPawnPromote netShowPawnPromote;
      t_netRecievePawnPromote netRecievePawnPromote;
      t_netPlayAccepted netPlayAccepted;
   };

};

#endif
