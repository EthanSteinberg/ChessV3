#include "chessGui.h"

#include "chessComponent.h"
#include "chessMenu.h"

#include <ClanLib/core.h>
#include <ClanLib/gl.h>
#include <ClanLib/display.h>
#include <ClanLib/gui.h>
#include <ClanLib/sound.h>

#include <boost/make_shared.hpp>

#include <pantheios/inserters.hpp>
#include <pantheios/pantheios.hpp>

#define debug(X) pantheios::log(pantheios::debug,X)

using boost::shared_ptr;
using boost::make_shared;

void t_chessGui::run()
{
   gui->exec();
}

void t_chessGui::init()
{ 
   debug("Entering t_chessGui::init()");

   resources = make_shared<CL_ResourceManager>("../res/resources.xml");
   //gui = make_shared<CL_GUIManager>("res");
   gui = new CL_GUIManager("../res");
   
   createWindow();

   comp = make_shared<t_chessComponent>(window.get(),resources);
   menu = make_shared<t_chessMenu>(window.get(),resources);
   label = make_shared<CL_Label>(window.get());
   
   label->set_text("Wow this sucks");
   
   resizedFunc();
}


void t_chessGui::createWindow()
{
   CL_DisplayWindowDescription window_desc;
   window_desc.set_size(CL_Size(sizex, sizey), true);
   window_desc.set_title("Chess");
   window_desc.set_allow_resize(true);
   
   //window = make_shared<CL_Window>(gui.get(),window_desc);
   window = make_shared<CL_Window>(gui,window_desc);

   window->func_resized().set(this,&t_chessGui::resizedFunc);
   window->func_close().set(this,&t_chessGui::closeFunc);
}

void t_chessGui::resizedFunc()
{
   CL_Rect client_area = window->get_client_area();
   menu->set_geometry(CL_Rect(client_area.left,client_area.top,client_area.right,client_area.top+20));
   menu->request_repaint();
   
   label->set_geometry(CL_Rect(client_area.left,client_area.top+50 ,client_area.right,client_area.top+50 + 15));
   label->request_repaint();
   
   comp->set_geometry(CL_Rect(client_area.left,client_area.top+50 + 15,client_area.right,client_area.bottom));
   comp->request_repaint();
   
}
   
bool t_chessGui::closeFunc()
{
   gui->exit_with_code(0);
   return true;
}
