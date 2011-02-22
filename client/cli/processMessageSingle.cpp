#include <iostream>

#include <boost/thread.hpp>
#include <boost/foreach.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessCli.h"
#include "messages.h"

bool t_chessCli::processMessageSingle(const t_message &message)
{
   switch (message.id)
   {

   case BOARD_CLICKED:
   {
      std::vector<t_message> messageBuffer = chessEngine.boardClickedSingle(message);

      {
         boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

         BOOST_FOREACH(t_message &newMessage, messageBuffer)
         {
            sharedData.clientBuffer.push_front(newMessage);
         }
         sharedData.clientCondition.notify_one();
      }

      break;
   }

   case JOIN_SERVER:
   {
      std::cout<<"Telling net to join the server"<<std::endl;

      {
         boost::unique_lock<boost::mutex> lock(sharedData.netMutex);

         sharedData.netBuffer.push_front(message);
         sharedData.netCondition.notify_one();
      }

      break;
   }

   case WANT_REFRESH_CONNECTION:
   {
      std::cout<<"Telling net to refresh my data"<<std::endl;

      t_message newMessage;
      newMessage.id = REFRESH_CONNECTION;
      strcpy(newMessage.refreshConnection.server,"Not Connected");

      {
         boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

         sharedData.clientBuffer.push_front(newMessage);
         sharedData.clientCondition.notify_one();
      }

      break;
   }

   case REFRESH_CONNECTION:
   {
      std::cout<<"Unconnected stuff should never get this"<<std::endl;

      for (auto iter = message.dataPackets.begin(); iter != message.dataPackets.end(); iter++)
      {
         std::cout<<iter->name<<std::endl;
      }

      {
         boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

         sharedData.clientBuffer.push_front(message);
         sharedData.clientCondition.notify_one();
      }

      break;
   }

   case CONNECTION_SUCCESS:
   {
      std::cout<<"Cli told about the awesomeness of an actual network connection"<<std::endl;

      connected = 1;

      {
         boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

         sharedData.clientBuffer.push_front(message);
         sharedData.clientCondition.notify_one();
      }
      break;
   }

   case CONNECTION_BAD_NAME:
   {
      std::cout<<"Cli told about the fail of bad name choice"<<std::endl;

      {
         boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

         sharedData.clientBuffer.push_front(message);
         sharedData.clientCondition.notify_one();
      }
      break;
   }

   case CONNECTION_NO_SERVER:
   {
      std::cout<<"No server that you requested"<<std::endl;
      {
         boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

         sharedData.clientBuffer.push_front(message);
         sharedData.clientCondition.notify_one();
      }
      break;
   }

   case WANT_TO_RESET_BOARD:
   {
      std::cout<<"Gui wants to reset the board"<<std::endl;

      t_message newMessage;
      newMessage.id = RESET_WARNING_SINGLE;

      {
         boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

         sharedData.clientBuffer.push_front(newMessage);
         sharedData.clientCondition.notify_one();
      }
      break;
   }

   case RESET_PAST_WARNING:
   {
      std::cout<<"Gui wants to reset past the warning"<<std::endl;

      t_message newMessage;
      newMessage.id = RESET_GUI;
      {
         boost::unique_lock<boost::mutex> lock(sharedData.netMutex);

         sharedData.clientBuffer.push_front(newMessage);
         sharedData.clientCondition.notify_one();
      }

      chessEngine.reset();

      break;
   }

   case QUIT_MESSAGE:
   {
      std::cout<<"Cli told to quit"<<std::endl;
      {
         boost::unique_lock<boost::mutex> lock(sharedData.netMutex);

         sharedData.netBuffer.push_front(message);
         sharedData.netCondition.notify_one();
      }
   }
   return 1;

   default:
      std::cout<<"And I do not know what it was"<<std::endl;

   }

   return 0;
}
