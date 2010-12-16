#ifndef CHESS_SERVER_SELECT_H_INCLUDED
#define CHESS_SERVER_SELECT_H_INCLUDED

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <ClanLib/core.h>
#include <ClanLib/csslayout.h>
#include <ClanLib/GUI/Components/window.h>

class CL_ResourceManager;

class t_chessServerSelect : boost::noncopyable, public CL_Window
{
public:
   t_chessServerSelect(CL_GUIComponent *parent, boost::shared_ptr<CL_ResourceManager> resPtr);

private:
   void renderFunc(CL_GraphicContext &gc, const CL_Rect &clip_rect);
   void resizeFunc();
   void messageFunc(CL_GUIMessage &lol);

   boost::shared_ptr<CL_ResourceManager> resources;
};

#endif
