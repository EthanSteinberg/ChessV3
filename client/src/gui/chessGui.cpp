#include "chessGui.h"

#include "../messages.h"

#include <boost/bind.hpp>

#include <SFML/Graphics.hpp>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/CEGUIOpenGLRenderer.h>

#include <iostream>

t_chessGui::t_chessGui(t_sharedData &theSharedData) : App(sf::VideoMode(800,820,32), "Chess Window"), sharedData(theSharedData), width(100), height(100), newWidth(800), newHeight(820)
{
   boardColors = {};
}

bool quitApp(sf::RenderWindow &App,t_sharedData &sharedData, const CEGUI::EventArgs &e)
{
   App.Close();

   t_message message;

   message.id = QUIT_MESSAGE;

   {
      boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

      sharedData.gameBuffer.push_back(message);
   }

   sharedData.gameCondition.notify_one();

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
   BlueBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(0,0,255));
   BrownBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(255,255,0));
   PurpleBox = sf::Shape::Rectangle(0,0,100,100,sf::Color(160,32,240));

   while (App.IsOpened())
   {
      processEvents();

      checkBuffer();

      App.Clear();

      drawBoard();

      CEGUI::System::getSingleton().renderGUI();

      App.Display();
   }

   return;
}

void t_chessGui::checkBuffer()
{
   t_message message;

   {
      boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

      while (!sharedData.clientBuffer.empty())
      {
         message = sharedData.clientBuffer.back();
         sharedData.clientBuffer.pop_back();

         switch (message.id)
         {
         case HIGHLIGHT_SPACE:
         {
            std::cout<<"I was told to highlight the space "<<message.highlightSpace.color<<std::endl;
            std::cout<<"It was at "<<message.highlightSpace.pos<<std::endl;
            std::cout<<std::endl;

            t_myVector2 pos = message.highlightSpace.pos;

            boardColors[pos.y *8 + pos.x] = message.highlightSpace.color;
            break;
         }

         case MOVE_PIECE:
         {
            std::cout<<"I was told to move a piece"<<std::endl;

            t_myVector2 oldPos = message.movePiece.oldPos;
            t_myVector2 pos = message.movePiece.pos;

            sprites[boardPieces[oldPos.y][oldPos.x]].SetPosition(pos.x * width, pos.y * height + 20);

            boardPieces[pos.y][pos.x] = boardPieces[oldPos.y][oldPos.x];
            //boardPieces[oldPos.y][oldPos.x] = 0;

            break;
         }


         default:
            std::cout<<"The client does not know what it recieved"<<std::endl;
         }
      }
   }
}


void t_chessGui::drawBoard()
{
   for (int y = 0; y<8; y++)
   {
      for (int x =0 ; x<8; x++)
      {
         if (boardColors[y*8 + x] == 1)
         {
            BlueBox.SetPosition(x*width,y*height +20);
            App.Draw(BlueBox);
         }

         else if (boardColors[y*8 + x] == 2)
         {
            BrownBox.SetPosition(x*width,y*height +20);
            App.Draw(BrownBox);
         }

         else if (boardColors[y*8 + x] == 3)
         {
            PurpleBox.SetPosition(x*width,y*height +20);
            App.Draw(PurpleBox);
         }

         else if ((x+y)%2)
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
   myRoot->setMousePassThroughEnabled(true);

   CEGUI::MenuItem *quitItem = static_cast<CEGUI::MenuItem *>(wmgr->getWindow("Root/FrameWindow/Menubar/File/Exit"));
   quitItem->subscribeEvent(CEGUI::MenuItem::EventClicked,CEGUI::Event::Subscriber(boost::bind(quitApp,boost::ref(App),boost::ref(sharedData),_1)));
}

void t_chessGui::processEvents()
{
   sf::Event event;

   bool resized = 0;

   while (App.GetEvent(event))
   {
      if (event.Type == sf::Event::Closed)
      {
         App.Close();
         t_message message;

         message.id = QUIT_MESSAGE;

         {
            boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

            sharedData.gameBuffer.push_back(message);
         }

         sharedData.gameCondition.notify_one();
      }

      else if (event.Type == sf::Event::MouseMoved)
      {
         mySystem->injectMousePosition(event.MouseMove.X,event.MouseMove.Y);
      }

      else if (event.Type == sf::Event::MouseButtonPressed)
      {
         bool handled = mySystem->injectMouseButtonDown(chessCegui.mouse(event.MouseButton.Button));

         if (event.MouseButton.Y > (20.0/820.0 * newHeight) && !handled) // If I press a box
         {
            int x = (event.MouseButton.X)/(newWidth/8);
            int y = (event.MouseButton.Y + -20.0/820.0 * newHeight)/(newHeight/8);

            //std::cout<<event.MouseButton.X<<' '<<event.MouseButton.Y<<std::endl;
            //std::cout<<x<<' '<<y<<std::endl;
            //std::cout<<std::endl;


            t_message message;

            message.id = BOARD_CLICKED;
            message.boardClicked.pos.x = x;
            message.boardClicked.pos.y = y;

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_back(message);
            }

            sharedData.gameCondition.notify_one();
         }
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
      boardPieces[6][i] = i;
   }

   sprites[8].SetImage(images[3]);
   sprites[8].SetPosition(0 * width,height*7 + 20);
   boardPieces[7][0] = 8;

   sprites[9].SetImage(images[1]);
   sprites[9].SetPosition(1 * width,height*7 + 20);
   boardPieces[7][1] = 9;

   sprites[10].SetImage(images[2]);
   sprites[10].SetPosition(2 * width,height*7 + 20);
   boardPieces[7][2] = 10;

   sprites[11].SetImage(images[5]);
   sprites[11].SetPosition(3 * width,height*7 + 20);
   boardPieces[7][3] = 11;

   sprites[12].SetImage(images[4]);
   sprites[12].SetPosition(4 * width,height*7 + 20);
   boardPieces[7][4] = 12;

   sprites[13].SetImage(images[2]);
   sprites[13].SetPosition(5 * width,height*7 + 20);
   boardPieces[7][5] = 13;

   sprites[14].SetImage(images[1]);
   sprites[14].SetPosition(6 * width,height*7 + 20);
   boardPieces[7][6] = 14;

   sprites[15].SetImage(images[3]);
   sprites[15].SetPosition(7 * width,height*7 + 20);
   boardPieces[7][7] = 15;

   //Load blacks
   for (int i = 0; i<8; i++)
   {
      sprites[i+16].SetImage(images[6]);
      sprites[i+16].SetPosition(i * width,height*1 + 20);
      boardPieces[1][i] = i + 16;
   }

   sprites[24].SetImage(images[9]);
   sprites[24].SetPosition(0 * width,height*0 + 20);
   boardPieces[0][0] = 24;

   sprites[25].SetImage(images[7]);
   sprites[25].SetPosition(1 * width,height*0 + 20);
   boardPieces[0][1] = 25;

   sprites[26].SetImage(images[8]);
   sprites[26].SetPosition(2 * width,height*0 + 20);
   boardPieces[0][2] = 26;

   sprites[27].SetImage(images[11]);
   sprites[27].SetPosition(3 * width,height*0 + 20);
   boardPieces[0][3] = 27;

   sprites[28].SetImage(images[10]);
   sprites[28].SetPosition(4 * width,height*0 + 20);
   boardPieces[0][4] = 28;

   sprites[29].SetImage(images[8]);
   sprites[29].SetPosition(5 * width,height*0 + 20);
   boardPieces[0][5] = 29;

   sprites[30].SetImage(images[7]);
   sprites[30].SetPosition(6 * width,height*0 + 20);
   boardPieces[0][6] = 30;

   sprites[31].SetImage(images[9]);
   sprites[31].SetPosition(7 * width,height*0 + 20);
   boardPieces[0][7] = 31;
}
