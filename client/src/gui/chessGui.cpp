#include "chessGui.h"

#include <SFML/Graphics.hpp>

#include <iostream>
void t_chessGui::run()
{
   sf::RenderWindow App(sf::VideoMode(800,800,32), "Testing Window");   

   sf::Event event;
   sf::Shape RedBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(255,0,0));
   sf::Shape BlackBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(0,255,0));
   
   while (App.IsOpened())
   {
      
      while (App.GetEvent(event))
      {
         if (event.Type == sf::Event::Closed)
            App.Close();
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

      App.Display();
   }

   return;
}
