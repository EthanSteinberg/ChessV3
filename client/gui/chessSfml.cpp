#include "chessGui.h"
#include "messages.h"

#include <boost/bind.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cstring>

void t_chessGui::initSfml()
{
   loadImages();
   loadSprites();


   RedBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(255,0,0));
   BlackBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(0,255,0));
   BlueBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(0,0,255));
   BrownBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(255,255,0));
   PurpleBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(160,32,240));
   PinkBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(255,182,193));
}

bool t_chessGui::drawBoard(GdkEventExpose *event)
{
   sf::Event event2;

   while (App.GetEvent(event2)) ;

   App.Clear();

   for (int y = 0; y<8; y++)
   {
      for (int x =0 ; x<8; x++)
      {
         if (boardColors[y*8 + x] == 1)
         {
            BlueBox.SetPosition(x*width,y*height);
            App.Draw(BlueBox);
         }

         else if (boardColors[y*8 + x] == 2)
         {
            BrownBox.SetPosition(x*width,y*height);
            App.Draw(BrownBox);
         }

         else if (boardColors[y*8 + x] == 3)
         {
            PurpleBox.SetPosition(x*width,y*height);
            App.Draw(PurpleBox);
         }

         else if (boardColors[y*8 + x] == 4)
         {
            PinkBox.SetPosition(x*width,y*height);
            App.Draw(PinkBox);
         }

         else if ((x+y)%2)
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


   for (int i =0; i<32; i++)
   {
      App.Draw(sprites[i]);
   }

   App.Display();

   return true;
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


void t_chessGui::reset()
{
   boardPieces = {};
   boardColors = {};

   for (int i = 0 ;i < 32;i++)
      sprites[i].SetPosition(8 * width, 8 * height);
}

void t_chessGui::set()
{
   boardPieces = {};
   boardColors = {};

   for (int i = 0; i<8; i++)
   {
      sprites[i].SetPosition(i * width,height*6);
      boardPieces[6][i] = i;
   }

   sprites[8].SetPosition(0 * width,height*7);
   boardPieces[7][0] = 8;

   sprites[9].SetPosition(1 * width,height*7);
   boardPieces[7][1] = 9;

   sprites[10].SetPosition(2 * width,height*7);
   boardPieces[7][2] = 10;

   sprites[11].SetPosition(3 * width,height*7);
   boardPieces[7][3] = 11;

   sprites[12].SetPosition(4 * width,height*7);
   boardPieces[7][4] = 12;

   sprites[13].SetPosition(5 * width,height*7);
   boardPieces[7][5] = 13;

   sprites[14].SetPosition(6 * width,height*7);
   boardPieces[7][6] = 14;

   sprites[15].SetPosition(7 * width,height*7);
   boardPieces[7][7] = 15;

   //Load blacks
   for (int i = 0; i<8; i++)
   {
      sprites[i+16].SetPosition(i * width,height*1);
      boardPieces[1][i] = i + 16;
   }

   sprites[24].SetPosition(0 * width,height*0);
   boardPieces[0][0] = 24;

   sprites[25].SetPosition(1 * width,height*0);
   boardPieces[0][1] = 25;

   sprites[26].SetPosition(2 * width,height*0);
   boardPieces[0][2] = 26;

   sprites[27].SetPosition(3 * width,height*0);
   boardPieces[0][3] = 27;

   sprites[28].SetPosition(4 * width,height*0);
   boardPieces[0][4] = 28;

   sprites[29].SetPosition(5 * width,height*0);
   boardPieces[0][5] = 29;

   sprites[30].SetPosition(6 * width,height*0);
   boardPieces[0][6] = 30;

   sprites[31].SetPosition(7 * width,height*0);
   boardPieces[0][7] = 31;

   myArea->queue_draw();
}


void t_chessGui::loadSprites()
{
   for (int i = 0; i<8; i++)
   {
      sprites[i].SetImage(images[0]);
      sprites[i].SetPosition(i * width,height*6);
      boardPieces[6][i] = i;
   }

   sprites[8].SetImage(images[3]);
   sprites[8].SetPosition(0 * width,height*7);
   boardPieces[7][0] = 8;

   sprites[9].SetImage(images[1]);
   sprites[9].SetPosition(1 * width,height*7);
   boardPieces[7][1] = 9;

   sprites[10].SetImage(images[2]);
   sprites[10].SetPosition(2 * width,height*7);
   boardPieces[7][2] = 10;

   sprites[11].SetImage(images[5]);
   sprites[11].SetPosition(3 * width,height*7);
   boardPieces[7][3] = 11;

   sprites[12].SetImage(images[4]);
   sprites[12].SetPosition(4 * width,height*7);
   boardPieces[7][4] = 12;

   sprites[13].SetImage(images[2]);
   sprites[13].SetPosition(5 * width,height*7);
   boardPieces[7][5] = 13;

   sprites[14].SetImage(images[1]);
   sprites[14].SetPosition(6 * width,height*7);
   boardPieces[7][6] = 14;

   sprites[15].SetImage(images[3]);
   sprites[15].SetPosition(7 * width,height*7);
   boardPieces[7][7] = 15;

   //Load blacks
   for (int i = 0; i<8; i++)
   {
      sprites[i+16].SetImage(images[6]);
      sprites[i+16].SetPosition(i * width,height*1);
      boardPieces[1][i] = i + 16;
   }

   sprites[24].SetImage(images[9]);
   sprites[24].SetPosition(0 * width,height*0);
   boardPieces[0][0] = 24;

   sprites[25].SetImage(images[7]);
   sprites[25].SetPosition(1 * width,height*0);
   boardPieces[0][1] = 25;

   sprites[26].SetImage(images[8]);
   sprites[26].SetPosition(2 * width,height*0);
   boardPieces[0][2] = 26;

   sprites[27].SetImage(images[11]);
   sprites[27].SetPosition(3 * width,height*0);
   boardPieces[0][3] = 27;

   sprites[28].SetImage(images[10]);
   sprites[28].SetPosition(4 * width,height*0);
   boardPieces[0][4] = 28;

   sprites[29].SetImage(images[8]);
   sprites[29].SetPosition(5 * width,height*0);
   boardPieces[0][5] = 29;

   sprites[30].SetImage(images[7]);
   sprites[30].SetPosition(6 * width,height*0);
   boardPieces[0][6] = 30;

   sprites[31].SetImage(images[9]);
   sprites[31].SetPosition(7 * width,height*0);
   boardPieces[0][7] = 31;
}
