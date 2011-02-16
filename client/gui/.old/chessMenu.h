#ifndef CHESS_MENU_H_INCLUDED
#define CHESS_MENU_H_INCLUDED

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>

#include <ClanLib/GUI/gui_component.h>

class CL_Image;
class CL_ResourceManager;
class CL_MenuBar;
class CL_PopupMenu;

class t_chessMenu : boost::noncopyable, public CL_GUIComponent
{
public:

   t_chessMenu(CL_GUIComponent *parent, boost::shared_ptr<CL_ResourceManager> resPtr);

private:   
   void renderFunc(CL_GraphicContext &gc, const CL_Rect &clip_rect);
   void resizeFunc();
   void messageFunc(CL_GUIMessage &lol);
   void buttonPushed();

   boost::shared_ptr<CL_Image> boardImage;
   boost::shared_ptr<CL_ResourceManager> resources;
   
   boost::shared_ptr<CL_MenuBar> menuBar;
   boost::shared_ptr<CL_PopupMenu> popupMenu;

};


#endif
