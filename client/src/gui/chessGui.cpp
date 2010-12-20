#include "chessGui.h"

#include "../messages.h"

#include <boost/bind.hpp>

#include <SFML/Graphics.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

#include <iostream>

t_chessGui::t_chessGui(t_sharedData &theSharedData) : App(sf::VideoMode(800,820,32), "Chess Window"), sharedData(theSharedData)
{
}

bool quitApp(sf::RenderWindow &App, const CEGUI::EventArgs &e)
{
   App.Close();
   return true;
}

void t_chessGui::run()
{
   chessCegui.init();
   loadImages();
   loadSprites();

   initCegui();
   initServer();
   initConnect();

   RedBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(255,0,0));
   BlackBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(0,255,0));

   while (App.IsOpened())
   {
      processEvents();

      App.Clear();

      drawBoard();

      CEGUI::System::getSingleton().renderGUI();

      App.Display();
   }

   return;
}

void t_chessGui::drawBoard()
{
   for (int y = 0; y<8; y++)
   {
      for (int x =0 ; x<8; x++)
      {
         if ((x+y)%2)
         {
            BlackBox.SetPosition(x*width,y*height +20);
            App.Draw(BlackBox);
         }

         else
         {
            RedBox.SetPosition(x*width,y*height + 20);
            App.Draw(RedBox);
         }

      }
   }

   for (int i =0; i<32; i++)
   {
      App.Draw(sprites[i]);
   }
}

void t_chessGui::loadImages()
{
   char buffer[40];

   for (int i = 0; i<12; i++)
   {
      snprintf(buffer,sizeof(buffer),"../res/ChessPics/%d.png",i);

      images[i].LoadFromFile(buffer);
   }

}

void t_chessGui::initCegui()
{
   //CEGUI::OpenGLRenderer &myRenderer =
   CEGUI::OpenGLRenderer::bootstrapSystem();

   CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");

   mySystem = CEGUI::System::getSingletonPtr();
   wmgr = CEGUI::WindowManager::getSingletonPtr();

   myRoot = wmgr->loadWindowLayout("main.layout");
   mySystem->setGUISheet(myRoot);

   CEGUI::MenuItem *quitItem = static_cast<CEGUI::MenuItem *>(wmgr->getWindow("Root/FrameWindow/Menubar/File/Exit"));
   quitItem->subscribeEvent(CEGUI::MenuItem::EventClicked,CEGUI::Event::Subscriber(boost::bind(quitApp,boost::ref(App),_1)));
}

void t_chessGui::processEvents()
{
   sf::Event event;

   int newWidth;
   int newHeight;

   bool resized = 0;

   while (App.GetEvent(event))
   {
      if (event.Type == sf::Event::Closed)
      {
         App.Close();
      }

      else if (event.Type == sf::Event::MouseMoved)
      {
         mySystem->injectMousePosition(event.MouseMove.X,event.MouseMove.Y);
      }

      else if (event.Type == sf::Event::MouseButtonPressed)
      {
         mySystem->injectMouseButtonDown(chessCegui.mouse(event.MouseButton.Button));
      }

      else if (event.Type == sf::Event::MouseButtonReleased)
      {
         mySystem->injectMouseButtonUp(chessCegui.mouse(event.MouseButton.Button));
      }

      else if (event.Type == sf::Event::TextEntered)
      {
         mySystem->injectChar(event.Text.Unicode);
      }

      else if (event.Type == sf::Event::KeyPressed)
      {
         mySystem->injectKeyDown(chessCegui.key(event.Key.Code));
      }

      else if (event.Type == sf::Event::KeyReleased)
      {
         mySystem->injectKeyUp(chessCegui.key(event.Key.Code));
      }

      else if (event.Type == sf::Event::Resized)
      {
         resized = 1;
         newWidth = event.Size.Width;
         newHeight = event.Size.Height;
      }
   }

   if (resized)
   {
      mySystem->notifyDisplaySizeChanged(CEGUI::Size(newWidth,newHeight));
   }
}

void t_chessGui::loadSprites()
{
   for (int i = 0; i<8; i++)
   {
      sprites[i].SetImage(images[0]);
      sprites[i].SetPosition(i * width,height*6 + 20);
   }

   sprites[8].SetImage(images[3]);
   sprites[8].SetPosition(0 * width,height*7 + 20);

   sprites[9].SetImage(images[1]);
   sprites[9].SetPosition(1 * width,height*7 + 20);

   sprites[10].SetImage(images[2]);
   sprites[10].SetPosition(2 * width,height*7 + 20);

   sprites[11].SetImage(images[5]);
   sprites[11].SetPosition(3 * width,height*7 + 20);

   sprites[12].SetImage(images[4]);
   sprites[12].SetPosition(4 * width,height*7 + 20);

   sprites[13].SetImage(images[2]);
   sprites[13].SetPosition(5 * width,height*7 + 20);

   sprites[14].SetImage(images[1]);
   sprites[14].SetPosition(6 * width,height*7 + 20);

   sprites[15].SetImage(images[3]);
   sprites[15].SetPosition(7 * width,height*7 + 20);

   //Load blacks
   for (int i = 0; i<8; i++)
   {
      sprites[i+16].SetImage(images[6]);
      sprites[i+16].SetPosition(i * width,height*1 + 20);
   }

   sprites[24].SetImage(images[9]);
   sprites[24].SetPosition(0 * width,height*0 + 20);

   sprites[25].SetImage(images[7]);
   sprites[25].SetPosition(1 * width,height*0 + 20);

   sprites[26].SetImage(images[8]);
   sprites[26].SetPosition(2 * width,height*0 + 20);

   sprites[27].SetImage(images[11]);
   sprites[27].SetPosition(3 * width,height*0 + 20);

   sprites[28].SetImage(images[10]);
   sprites[28].SetPosition(4 * width,height*0 + 20);

   sprites[29].SetImage(images[8]);
   sprites[29].SetPosition(5 * width,height*0 + 20);

   sprites[30].SetImage(images[7]);
   sprites[30].SetPosition(6 * width,height*0 + 20);

   sprites[31].SetImage(images[9]);
   sprites[31].SetPosition(7 * width,height*0 + 20);
}
