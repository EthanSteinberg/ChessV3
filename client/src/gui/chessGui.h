#ifndef CHESS_GUI_H_INCLUDED
#define CHESS_GUI_H_INCLUDED

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <map>
#include <string>

#include "chessCegui.h"

class t_sharedData;

class t_chessGui : boost::noncopyable
{
public:
   t_chessGui(t_sharedData &theSharedData);

   void run();

private:
   void processEvents();
   void drawBoard();
   
   void loadImages();
   void loadSprites();

   void initServer();
   void initConnect();
   void initCegui();

   void checkBuffer();

   t_chessCegui chessCegui;

   sf::RenderWindow App;

   sf::Image images[12];

   sf::Sprite sprites[32];

   sf::Shape BlackBox;
   sf::Shape RedBox;
   sf::Shape BlueBox;
   sf::Shape BrownBox;
   sf::Shape PurpleBox;
   sf::Shape PinkBox;

   CEGUI::Window *myRoot;
   CEGUI::System *mySystem;
   CEGUI::WindowManager *wmgr;

   t_sharedData &sharedData;

   int boardColors[64];

   int boardPieces[8][8];

   const int width;
   const int height;

   int newWidth;
   int newHeight;
};

#endif
