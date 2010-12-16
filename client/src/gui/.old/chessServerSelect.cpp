#include "chessServerSelect.h"

#include <ClanLib/display.h>
   
#include <boost/make_shared.hpp>

using boost::make_shared;
using boost::shared_ptr;

#include <pantheios/inserters.hpp>
#include <pantheios/pantheios.hpp>

#define debug(X) pantheios::log(pantheios::debug,X)

t_chessServerSelect::t_chessServerSelect(CL_GUIComponent *parent, shared_ptr<CL_ResourceManager> resPtr) : CL_Window(parent,CL_DisplayWindowDescription("Server Selection")), resources(resPtr)
{
   func_render().set(this,&t_chessServerSelect::renderFunc);
   func_resized().set(this,&t_chessServerSelect::resizeFunc);
   func_process_message().set(this,&t_chessServerSelect::messageFunc);
      
}

void t_chessServerSelect::renderFunc(CL_GraphicContext &gc, const CL_Rect &clip_rect)
{
}

void t_chessServerSelect::resizeFunc()
{
   debug("ServerSelect: resized");
}

void t_chessServerSelect::messageFunc(CL_GUIMessage &lol)
{
}
