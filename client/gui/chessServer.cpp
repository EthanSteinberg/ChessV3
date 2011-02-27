#include "chessGui.h"

#include "messages.h"

#include <boost/bind.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>

#include <cstring>


void t_chessGui::refreshConnect()
{
   t_message message;

   message.id = WANT_REFRESH_CONNECTION;

   {
      boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

      sharedData.gameBuffer.push_front(message);
   }

   sharedData.gameCondition.notify_one();
}

void t_chessGui::selectedPlay()
{
   t_message message;

   message.id = WANT_TO_PLAY_WITH;

   strcpy(message.wantToPlayWith.name,view->get_selection()->get_selected()->get_value(columns.m_Name).c_str());

   {
      boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

      sharedData.gameBuffer.push_front(message);
   }

   sharedData.gameCondition.notify_one();

   std::cout<<"The play button was pressed"<<std::endl;
}

void t_chessGui::openServer()
{
   refreshConnect();
   serverWindow->show();
}

void t_chessGui::openConnect()
{
   int result = connectDialog->run();

   switch (result)
   {
   case -4:
      //Closed by cancel or x
      break;

   case 1:
      //Accepted
      connectToServer();
      break;

   default:
      std::cout<<"Unhandled button "<<result<<std::endl;

      break;
   }

   connectDialog->hide();
}

void t_chessGui::connectToServer()
{


   t_message message;

   message.id = JOIN_SERVER;

   strcpy(message.joinServer.name,nameEntry->get_text().c_str());
   std::cout<<message.joinServer.name<<std::endl;

   strcpy(message.joinServer.address,serverEntry->get_text().c_str());
   std::cout<<message.joinServer.address<<std::endl;

   {
      boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

      sharedData.gameBuffer.push_front(message);
   }

   sharedData.gameCondition.notify_one();
}


void t_chessGui::disconnectFromServer()
{
   t_message message;
   message.id = DISCONNECT_MESSAGE;

   {
      boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

      sharedData.gameBuffer.push_front(message);
   }
   sharedData.gameCondition.notify_one();
   refreshConnect();
}

void t_chessGui::refreshServer(t_message message)
{
   list->clear();

   t_dataPacket data;
   char temp[40];

   
   for (unsigned int i = 0; i< message.dataPackets.size(); i++)
   {
      auto iter = list->append();
      std::cout<<"I am adding the row: "<<i<<std::endl;
      std::cout<<data.name<<" "<<data.status<<" "<<data.wins<<" "<<std::endl;

      data = message.dataPackets[i];
      iter->set_value(columns.m_Name, Glib::ustring(data.name));
      iter->set_value(columns.m_Status,data.status);
      iter->set_value(columns.m_Wins,data.wins);
      iter->set_value(columns.m_Losses,data.losses);
   }

   snprintf(temp,sizeof(temp),"You are connected to: %s",message.refreshConnection.server);
   label->set_text(temp);
}

void t_chessGui::showMessage(std::string textStuff)
{

   Gtk::MessageDialog message(textStuff);

   message.run();
}

void t_chessGui::showRequest(std::string textStuff)
{
   std::string temp = "Do you want to play with " + textStuff + "?";
   Gtk::MessageDialog message(temp, false, Gtk::MessageType::MESSAGE_QUESTION, Gtk::ButtonsType::BUTTONS_YES_NO);

   int result = message.run();

   t_message newMessage;
   newMessage.id = PLAY_RESPONSE;

   if (result == GTK_RESPONSE_YES)
   {
      set();
      newMessage.playResponse.response = 1;

      int result2 = chooseSideDialog->run();

      while (result2 != 0)
      {
         showMessage("You must choose a side to play as");
         result2 = chooseSideDialog->run();
      }

     chooseSideDialog->hide(); 

     if (whiteButton->get_active())
        newMessage.playResponse.side = 0;

     else
        newMessage.playResponse.side = 1;
   }

   else
   {
      newMessage.playResponse.response = 0;
   }

   strcpy(newMessage.playResponse.name,textStuff.c_str());

   {
      boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

      sharedData.gameBuffer.push_front(newMessage);
   }
   sharedData.gameCondition.notify_one();

}

