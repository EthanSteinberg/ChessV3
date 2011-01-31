#include "chessGui.h"

#include "messages.h"

#include <boost/bind.hpp>

#include <SFML/Graphics.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

#include <iostream>

#include <cstring>

bool openServer(CEGUI::FrameWindow *server, const CEGUI::EventArgs &e)
{
   server->show();
   return true;
}

bool closeServer(CEGUI::FrameWindow *server, const CEGUI::EventArgs &e)
{
   server->hide();
   return true;
}

bool openConnect(CEGUI::FrameWindow *connect, const CEGUI::EventArgs &e)
{
   connect->show();
   return true;
}

bool closeConnect(CEGUI::FrameWindow *connect, const CEGUI::EventArgs &e)
{
   connect->hide();
   return true;
}

bool connectToServer(CEGUI::Editbox* name, CEGUI::Editbox* ip, t_sharedData &sharedData, const CEGUI::EventArgs &e)
{
   t_message message;

   message.id = JOIN_SERVER;
   
   strcpy(message.joinServer.name,name->getText().c_str());
   std::cout<<message.joinServer.name<<std::endl;
   
   strcpy(message.joinServer.address,ip->getText().c_str());
   std::cout<<message.joinServer.address<<std::endl;
   
   {
      boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

      sharedData.gameBuffer.push_back(message);
   }

   sharedData.gameCondition.notify_one();


   return true;
}


void t_chessGui::initServer()
{
   CEGUI::FrameWindow *server = static_cast<CEGUI::FrameWindow *>(wmgr->loadWindowLayout("server.layout"));
   myRoot->addChildWindow(server);
   server->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,CEGUI::Event::Subscriber(boost::bind(closeServer,server,_1)));


   CEGUI::MenuItem *serverItem = static_cast<CEGUI::MenuItem *>(wmgr->getWindow("Root/FrameWindow/Menubar/File/New"));
   serverItem->subscribeEvent(CEGUI::MenuItem::EventClicked,CEGUI::Event::Subscriber(boost::bind(openServer,server,_1)));


   CEGUI::MultiColumnList *testing = static_cast<CEGUI::MultiColumnList *>(wmgr->getWindow("Lols3"));
   testing->addColumn("Names",0,CEGUI::UDim(.25,0));
   testing->addColumn("Action",1,CEGUI::UDim(.25,0));
   testing->addColumn("Wins",2,CEGUI::UDim(.25,0));
   testing->addColumn("Losses",3,CEGUI::UDim(.25,0));

   testing->addRow();
   testing->addRow();

   testing->setItem(new CEGUI::ListboxTextItem("What, wow,"),0u,0u);

   server->hide();
}

void t_chessGui::initConnect()
{
   CEGUI::FrameWindow *connect = static_cast<CEGUI::FrameWindow *>(wmgr->loadWindowLayout("connect.layout"));

   myRoot->addChildWindow(connect);
   connect->subscribeEvent(CEGUI::FrameWindow::EventCloseClicked,CEGUI::Event::Subscriber(boost::bind(closeConnect,connect,_1)));

   CEGUI::MenuItem *connectItem = static_cast<CEGUI::MenuItem *>(wmgr->getWindow("Root/FrameWindow/Menubar/File/Open"));
   connectItem->subscribeEvent(CEGUI::MenuItem::EventClicked,CEGUI::Event::Subscriber(boost::bind(openConnect,connect,_1)));

   CEGUI::MenuItem *newConnectItem = static_cast<CEGUI::MenuItem *>(wmgr->getWindow("Lols2"));
   newConnectItem->subscribeEvent(CEGUI::MenuItem::EventClicked,CEGUI::Event::Subscriber(boost::bind(openConnect,connect,_1)));



   CEGUI::PushButton *cancelConnect = static_cast<CEGUI::PushButton *>(wmgr->getWindow("1Lols6"));
   cancelConnect->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(boost::bind(closeConnect,connect,_1)));


   CEGUI::Editbox *name = static_cast<CEGUI::Editbox *>(wmgr->getWindow("1Lols2"));
   CEGUI::Editbox *ip = static_cast<CEGUI::Editbox *>(wmgr->getWindow("1Lols7"));


   CEGUI::PushButton *startConnection = static_cast<CEGUI::PushButton *>(wmgr->getWindow("1Lols4"));
   startConnection->subscribeEvent(CEGUI::PushButton::EventClicked,CEGUI::Event::Subscriber(boost::bind(connectToServer,name,ip,boost::ref(sharedData),_1)));

   connect->hide();
}

