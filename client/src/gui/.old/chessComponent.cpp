#include "chessComponent.h"

#include <ClanLib/display.h>
   
#include <boost/make_shared.hpp>

using boost::make_shared;
using boost::shared_ptr;

#include <pantheios/inserters.hpp>
#include <pantheios/pantheios.hpp>

#define debug(X) pantheios::log(pantheios::debug,X)

t_chessComponent::t_chessComponent(CL_GUIComponent *parent, shared_ptr<CL_ResourceManager> resPtr) : CL_GUIComponent(parent), resources(resPtr)
{
   
   func_render().set(this,&t_chessComponent::renderFunc);
   func_resized().set(this,&t_chessComponent::resizeFunc);
   func_process_message().set(this,&t_chessComponent::messageFunc);
      
   boardImage = make_shared<CL_Image>(get_gc(),"Board",resources.get()); 
}

void t_chessComponent::renderFunc(CL_GraphicContext &gc, const CL_Rect &clip_rect)
{
   debug("component: drawn");
   boardImage->draw(gc,clip_rect);
}

void t_chessComponent::resizeFunc()
{
   debug("component: resized");
}

void t_chessComponent::messageFunc(CL_GUIMessage &lol)
{
}
