#ifndef CHESS_SERVER_H_INCLUDED
#define CHESS_SERVER_H_INCLUDED

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <map>
#include <string>

#include "chessCegui.h"

class t_sharedData;

class t_chessServer : boost::noncopyable
{
public:
   t_chessServer(t_sharedData &theSharedData);

   void show();
   void run();

private:

   t_chessCegui chessCegui;
   
   sf::RenderWindow App;

   const static int width = 100;
   const static int height = 100;
};
#endif
