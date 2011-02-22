#include "chessGui.h"
#include "messages.h"

#include <boost/bind.hpp>

#include <SFML/Graphics.hpp>
#include <iostream>

t_chessGui::t_chessGui(t_sharedData &theSharedData) : sharedData(theSharedData), width(100), height(100), newWidth(800), newHeight(800), showingCheck(0)
{

   boardColors = {};
}

bool quitApp(sf::RenderWindow &App,t_sharedData &sharedData)
{
   App.Close();

   t_message message;

   message.id = QUIT_MESSAGE;

   {
      boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

      sharedData.gameBuffer.push_front(message);
   }

   sharedData.gameCondition.notify_one();

   return true;
}


void t_chessGui::run()
{
   initGtkmm();

   initSfml();


   Glib::signal_timeout().connect(sigc::mem_fun(*this, &t_chessGui::checkBuffer),100);

   Gtk::Main::run(*mainWindow);
   quitApp(App,sharedData);

   return;
}
bool t_chessGui::checkBuffer()
{
   t_message message;

   while (1)
   {

      {
         boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

         if (sharedData.clientBuffer.empty())
         {
            break;
         }

         message = sharedData.clientBuffer.back();
         sharedData.clientBuffer.pop_back();

      }

      switch (message.id)
      {


      case HIGHLIGHT_SPACE:
      {
         //std::cout<<"I was told to highlight the space "<<message.highlightSpace.color<<std::endl;
         //std::cout<<"It was at "<<message.highlightSpace.pos<<std::endl;
         //std::cout<<std::endl;

         t_myVector2 pos = message.highlightSpace.pos;

         boardColors[pos.y *8 + pos.x] = message.highlightSpace.color;

         myArea->queue_draw();
         break;
      }

      case MOVE_PIECE:
      {
         //std::cout<<"I was told to move a piece"<<std::endl;

         t_myVector2 oldPos = message.movePiece.oldPos;
         t_myVector2 pos = message.movePiece.pos;

         sprites[boardPieces[oldPos.y][oldPos.x]].SetPosition(pos.x * width, pos.y * height);

         boardPieces[pos.y][pos.x] = boardPieces[oldPos.y][oldPos.x];
         //boardPieces[oldPos.y][oldPos.x] = 0;
         myArea->queue_draw();

         break;
      }

      case CAPTURE_PIECE:
      {
         //std::cout<<"I was told to capture a piece"<<std::endl;

         t_myVector2 oldPos = message.movePiece.oldPos;
         t_myVector2 pos = message.movePiece.pos;

         sprites[boardPieces[oldPos.y][oldPos.x]].SetPosition(pos.x * width, pos.y * height);
         sprites[boardPieces[pos.y][pos.x]].SetPosition(8 * width, 8 * height);


         boardPieces[pos.y][pos.x] = boardPieces[oldPos.y][oldPos.x];
         //boardPieces[oldPos.y][oldPos.x] = 0;

         myArea->queue_draw();
         break;
      }

      case RESET_GUI:
      {
         std::cout<<"Reseting the gui"<<std::endl;
         reset();

         break;
      }

      case PRESSED_BOARD_NOT_PLAYING:
      {
         std::cout<<"Pressed when connected but not playing"<<std::endl;
         showMessage("You have pressed the board but you are currently not in a game");
         break;
      }

      case CHECK_MATE:
      {
         if (message.checkMate.winner == 0)
         {
            showMessage("Checkmate baby, white won");
         }

         else
         {
            showMessage("Checkmate baby, black won");
         }

         break;
      }

      case IN_CHECK:
      {
         checkPos = message.inCheck.attackingPiece;
         std::cout<<checkPos<<std::endl;
         boardColors[checkPos.y *8 + checkPos.x] = 3;
         showingCheck = 1;
         
         showMessage("Sorry that move would leave you in check from this piece");

         myArea->queue_draw();
         break;
      }


      case RESET_WARNING_CONNECTED:
      {
         resetWarningConnected();
         break;
      }

      case RESET_WARNING_SINGLE:
      {
         resetWarningSingle();
         break;
      }

      case REFRESH_CONNECTION:
      {
         std::cout<<"Updating the connection"<<std::endl;
         refreshServer(message);

         break;
      }

      case PLAY_REQUEST:
      {
         std::cout<<"Gui is asking the user if he wants to play"<<std::endl;

         showRequest(message.playRequest.name);

         break;
      }

      case PLAY_ACCEPTED:
      {
         std::cout<<"My game attempt was accepted"<<std::endl;
         showMessage("The other person has accepted the game, good luck");
         break;
      }

      case PLAY_REJECTED:
      {
         std::cout<<"You efforts: failed"<<std::endl;
         showMessage("He/she has rejected your game");
         break;
      }

      case CONNECTION_SUCCESS:
      {
         std::cout<<"Showing the dialog box for good connect"<<std::endl;
         showMessage("Congrats you were able to connect");
         t_message newMessage;

         newMessage.id = WANT_REFRESH_CONNECTION;

         {
            boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

            sharedData.gameBuffer.push_front(newMessage);
         }

         sharedData.gameCondition.notify_one();

         break;
      }

      case CONNECTION_BAD_NAME:
      {
         std::cout<<"Showing the dialog box for bad name"<<std::endl;
         showMessage("Your name was invalid");

         t_message newMessage;

         newMessage.id = WANT_REFRESH_CONNECTION;

         {
            boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

            sharedData.gameBuffer.push_front(newMessage);
         }

         sharedData.gameCondition.notify_one();
         break;
      }

      case CONNECTION_NO_SERVER:
      {
         std::cout<<"Showing the dialog box for no server"<<std::endl;
         showMessage("The server did not respond");

         t_message newMessage;

         newMessage.id = WANT_REFRESH_CONNECTION;

         {
            boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

            sharedData.gameBuffer.push_front(newMessage);
         }

         sharedData.gameCondition.notify_one();
         break;
      }

      case CONNECTION_FAILED:
      {
         std::cout<<"Connection failed showing"<<std::endl;
         showMessage("The connection has failed somehow...");

         t_message newMessage;

         newMessage.id = WANT_REFRESH_CONNECTION;

         {
            boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

            sharedData.gameBuffer.push_front(newMessage);
         }

         sharedData.gameCondition.notify_one();
         break;
      }
      default:
         std::cout<<"The client does not know what it recieved"<<std::endl;
      }
   }

   return true;
}
