#ifndef CHESS_GUI_H_INCLUDED
#define CHESS_GUI_H_INCLUDED

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <map>
#include <string>

#include "chessCegui.h"

class t_chessGui : boost::noncopyable
{
public:
   t_chessGui();

   void run();

private:
   void drawBoard();
   void loadImages();

   t_chessCegui chessCegui;

   sf::RenderWindow App;

   sf::Image images[12];

   sf::Sprite testSpr;

   sf::Shape BlackBox;
   sf::Shape RedBox;

};

#endif
