#include "chessGui.h"

#include <SFML/Graphics.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

#include <iostream>
void t_chessGui::run()
{
   chessCegui.init();

   sf::RenderWindow App(sf::VideoMode(800,800,32), "Testing Window");   

   CEGUI::OpenGLRenderer& myRenderer = CEGUI::OpenGLRenderer::bootstrapSystem();


   CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );

   CEGUI::Window* myRoot = CEGUI::WindowManager::getSingleton().loadWindowLayout( "test.layout" );

   CEGUI::System &mySystem = CEGUI::System::getSingleton();
   
   mySystem.setGUISheet( myRoot );

   sf::Event event;
   sf::Shape RedBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(255,0,0));
   sf::Shape BlackBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(0,255,0));
   
   while (App.IsOpened())
   {
      
      while (App.GetEvent(event))
      {
         if (event.Type == sf::Event::Closed)
            App.Close();

         else if(event.Type == sf::Event::MouseMoved)
            mySystem.injectMousePosition( event.MouseMove.X,event.MouseMove.Y  );  

         else if(event.Type == sf::Event::MouseButtonPressed)
            mySystem.injectMouseButtonDown(chessCegui.mouse(event.MouseButton.Button));
         
         else if(event.Type == sf::Event::MouseButtonReleased)
            mySystem.injectMouseButtonUp(chessCegui.mouse(event.MouseButton.Button));
            
      }

      App.Clear();
      int width = 100;
      int height = 100;

      for (int y = 0;y<8;y++)
      {
         for (int x =0 ;x<8;x++)
         {
            if ((x+y)%2)
            {
               BlackBox.SetPosition(x*width,y*height);
               App.Draw(BlackBox);
            }

            else 
            {
               RedBox.SetPosition(x*width,y*height);
               App.Draw(RedBox);
            }

         }
      }
      CEGUI::System::getSingleton().renderGUI();
      App.Display();
   }

   return;
}
