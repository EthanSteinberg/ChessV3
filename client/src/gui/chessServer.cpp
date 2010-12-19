#include "chessServer.h"

#include <SFML/Graphics.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

#include <iostream>

#include <boost/thread.hpp>

t_chessServer::t_chessServer(t_sharedData &theSharedData) : App(sf::VideoMode(800,820,32), "Testing Window")
{
   chessCegui.init();
}

void t_chessServer::run()
{
   CEGUI::System &mySystem = CEGUI::System::getSingleton();
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
         mySystem.injectMousePosition(event.MouseMove.X,event.MouseMove.Y);
      }

      else if (event.Type == sf::Event::MouseButtonPressed)
      {
         mySystem.injectMouseButtonDown(chessCegui.mouse(event.MouseButton.Button));
      }

      else if (event.Type == sf::Event::MouseButtonReleased)
      {
         mySystem.injectMouseButtonUp(chessCegui.mouse(event.MouseButton.Button));
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
      mySystem.notifyDisplaySizeChanged(CEGUI::Size(newWidth,newHeight));
   }

   return;
}


void t_chessServer::show()
{
}
