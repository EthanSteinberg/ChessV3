#ifndef CHESS_COMPONENT_H_INCLUDED
#define CHESS_COMPONENT_H_INCLUDED

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>

#include <ClanLib/GUI/gui_component.h>

class CL_Image;
class CL_ResourceManager;

class t_chessComponent : boost::noncopyable, public CL_GUIComponent
{
public:

   t_chessComponent(CL_GUIComponent *parent, boost::shared_ptr<CL_ResourceManager> resPtr);

private:   
   void renderFunc(CL_GraphicContext &gc, const CL_Rect &clip_rect);
   void resizeFunc();
   void messageFunc(CL_GUIMessage &lol);

   boost::shared_ptr<CL_Image> boardImage;
   boost::shared_ptr<CL_ResourceManager> resources;
      

};


#endif
