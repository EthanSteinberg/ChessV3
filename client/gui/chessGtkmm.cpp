#include "chessGui.h"
#include "messages.h"

#include <boost/bind.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cstring>

#include <gtkmm.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>

void t_chessGui::resetWarningConnected()
{
   Gtk::MessageDialog message("Are you sure you want to start a new game and forfeit?" , false, Gtk::MessageType::MESSAGE_QUESTION, Gtk::ButtonsType::BUTTONS_OK_CANCEL);

   int result = message.run();


   if (result == GTK_RESPONSE_OK)

   {
      t_message newMessage;
      newMessage.id = RESET_PAST_WARNING;

      {
         boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

         sharedData.gameBuffer.push_front(newMessage);
      }
      sharedData.gameCondition.notify_one();
   }
}

void t_chessGui::resetWarningSingle()
{
   Gtk::MessageDialog message("Are you sure you want to start a new game and lose whatever data you have open?" , false, Gtk::MessageType::MESSAGE_QUESTION, Gtk::ButtonsType::BUTTONS_OK_CANCEL);

   int result = message.run();


   if (result == GTK_RESPONSE_OK)

   {
      t_message newMessage;
      newMessage.id = RESET_PAST_WARNING;

      {
         boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

         sharedData.gameBuffer.push_front(newMessage);
      }
      sharedData.gameCondition.notify_one();
   }
}

void t_chessGui::newButton()
{
   std::cout<<"The player wants to reset"<<std::endl;
   t_message message;

   message.id = WANT_TO_RESET_BOARD;

   {
      boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

      sharedData.gameBuffer.push_front(message);
   }

   sharedData.gameCondition.notify_one();
}


void t_chessGui::realizeFunc()
{
   std::cout<<"Realize the stuff"<<std::endl;
   App.Create(GDK_WINDOW_XID(myArea->get_window()->gobj()));
   App.SetFramerateLimit(60);
}

void t_chessGui::sizeAllocated(Gtk::Allocation &alloc)
{
   newWidth = alloc.get_width();
   newHeight = alloc.get_height();
}



void t_chessGui::initGtkmm()
{
   builder = Gtk::Builder::create_from_file("../res/mainLayout.glade");

   //builder->get_widget("liststore1",list);
   list = Gtk::ListStore::create(columns);

   builder->get_widget("treeview2",view);
   view->set_model(list);
   view->append_column("Names",columns.m_Name);
   view->append_column("Status",columns.m_Status);
   view->append_column("Wins",columns.m_Wins);
   view->append_column("Losses",columns.m_Losses);

   Gtk::Window *winPtr;

   builder->get_widget("window1",winPtr);
   mainWindow.reset(winPtr);

   builder->get_widget("window2",winPtr);
   serverWindow.reset(winPtr);


   Gtk::Dialog *diaPtr;
   builder->get_widget("dialog1",diaPtr);
   connectDialog.reset(diaPtr);

   builder->get_widget("dialog2",diaPtr);
   newGameDialog.reset(diaPtr);

   builder->get_widget("dialog3",diaPtr);
   singleSettings.reset(diaPtr);


   Gtk::MenuItem *network;
   builder->get_widget("networkMenu",network);
   network->signal_activate().connect(sigc::mem_fun(*this, &t_chessGui::openServer));

   builder->get_widget("menuitem7",network);
   network->signal_activate().connect(sigc::mem_fun(*this, &t_chessGui::openSingleSettings));

   builder->get_widget("drawingarea1",myArea);
   myArea->signal_realize().connect(sigc::mem_fun(*this,&t_chessGui::realizeFunc));
   myArea->signal_expose_event().connect(sigc::mem_fun(*this, &t_chessGui::drawBoard));
   myArea->signal_button_press_event().connect(sigc::mem_fun(*this, &t_chessGui::mouseButtonPressedEvent));
   myArea->signal_size_allocate().connect(sigc::mem_fun(*this, &t_chessGui::sizeAllocated));


   Gtk::Button *button;
   builder->get_widget("button10",button);
   button->signal_clicked().connect(sigc::mem_fun(*this, &t_chessGui::refreshConnect));

   builder->get_widget("button9",button);
   button->signal_clicked().connect(sigc::mem_fun(*this, &t_chessGui::disconnectFromServer));

   builder->get_widget("button8",button);
   button->signal_clicked().connect(sigc::mem_fun(*this, &t_chessGui::selectedPlay));

   builder->get_widget("button7",button);
   button->signal_clicked().connect(sigc::mem_fun(*this, &t_chessGui::openConnect));

   Gtk::ImageMenuItem *item;
   builder->get_widget("newButton",item);
   item->signal_activate().connect(sigc::mem_fun(*this, &t_chessGui::newButton));


   builder->get_widget("imagemenuitem1",item);
   item->signal_activate().connect(sigc::mem_fun(*this, &t_chessGui::openNewGame));

   builder->get_widget("entry4",serverEntry);
   builder->get_widget("entry3",nameEntry);
   builder->get_widget("label4",label);
   builder->get_widget("radiobutton1",Single);
   builder->get_widget("radiobutton2",Two);
   builder->get_widget("radiobutton6",customUci);
   builder->get_widget("button11",uciButton);

   customUci->signal_toggled().connect(sigc::mem_fun(*this, &t_chessGui::customUciToggled));


}

bool t_chessGui::mouseButtonPressedEvent(GdkEventButton *event)
{
   if (showingCheck)
   {
     boardColors[checkPos.y * 8 + checkPos.x] = 0; 
     showingCheck = 0;
   }

   int x = (event->x)/(newWidth/8);
   int y = (event->y)/(newHeight/8);

   //std::cout<<event.MouseButton.X<<' '<<event.MouseButton.Y<<std::endl;
   //std::cout<<x<<' '<<y<<std::endl;
   //std::cout<<std::endl;


   t_message message;

   message.id = BOARD_CLICKED;
   message.boardClicked.pos.x = x;
   message.boardClicked.pos.y = y;

   {
      boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

      sharedData.gameBuffer.push_front(message);
   }

   sharedData.gameCondition.notify_one();

   return true;
}

void t_chessGui::openNewGame()
{
   int result = newGameDialog->run();


   if (result == 1)

   {
      t_message newMessage;
      if (Single->get_active())
      {
         newMessage.id = NEW_GAME_TWO;
      }

      else
         newMessage.id = NEW_GAME_ONE;

      {
         boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

         sharedData.gameBuffer.push_front(newMessage);
      }
      sharedData.gameCondition.notify_one();
   }

   newGameDialog->hide();
}

void t_chessGui::openSingleSettings()
{
   int result = singleSettings->run();

   if (result == 1)
   {
   }

   singleSettings->hide();
}

void t_chessGui::customUciToggled()
{
   if (customUci->get_active())
   {
      uciButton->show();
   }

   else
   {
      uciButton->hide();
   }
}

