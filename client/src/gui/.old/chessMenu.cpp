#include "chessMenu.h"

#include <ClanLib/gui.h>
#include <ClanLib/display.h>
   
#include <boost/make_shared.hpp>
#include <boost/bind.hpp>

using boost::make_shared;
using boost::shared_ptr;

#include <pantheios/inserters.hpp>
#include <pantheios/pantheios.hpp>

#define debug(X) pantheios::log(pantheios::debug,X)

using boost::bind;

t_chessMenu::t_chessMenu(CL_GUIComponent *parent, shared_ptr<CL_ResourceManager> resPtr) : CL_GUIComponent(parent), resources(resPtr)
{
   func_render().set(this,&t_chessMenu::renderFunc);
   func_resized().set(this,&t_chessMenu::resizeFunc);
   func_process_message().set(this,&t_chessMenu::messageFunc);
      
   menuBar = make_shared<CL_MenuBar>(this);
   
   popupMenu = make_shared<CL_PopupMenu>();
   popupMenu->insert_item("Hello Peeps").func_clicked().set(this,&t_chessMenu::buttonPushed);

   menuBar->add_menu("Lols pops",*popupMenu);
}

void t_chessMenu::renderFunc(CL_GraphicContext &gc, const CL_Rect &clip_rect)
{
}

void t_chessMenu::resizeFunc()
{
   debug("t_chessMenu: resizing");
   menuBar->set_geometry(get_geometry());
}

void t_chessMenu::messageFunc(CL_GUIMessage &lol)
{
}

void t_chessMenu::buttonPushed()
{
   debug("t_chessMenu: pushed");
   std::cout<<"The button was pushed"<<std::endl;
}
