#include <iostream>

#include <boost/thread.hpp>
#include <boost/foreach.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessCli.h"
#include "../uci/chessUci.h"
#include "messages.h"

void createUci(t_sharedData &sharedData, int fd1, int fd2)
{
   t_chessUci newUci(sharedData,fd1,fd2);

   newUci.run();
}

bool t_chessCli::processMessageSingle(const t_message &message)
{
   switch (message.id)
   {

   case BOARD_CLICKED:
   {
      if (status  == PLAYING_TWO)
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
      }

      else if (status == PLAYING_ONE)
      {
         bool turn = chessEngine.getTurn();
         std::vector<t_message> messageBuffer = chessEngine.boardClickedSingle(message);


         {
            boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

            BOOST_FOREACH(t_message &newMessage, messageBuffer)
            {
               if (newMessage.id == CAPTURE_PIECE || newMessage.id == MOVE_PIECE)
               {
                  char temp[5];
                  temp[0] = newMessage.movePiece.oldPos.x + 'a';
                  temp[1] = '8' - newMessage.movePiece.oldPos.y;

                  temp[2] = newMessage.movePiece.pos.x + 'a';
                  temp[3] = '8' - newMessage.movePiece.pos.y;
                  temp[4] = 0;

                  std::cout<<temp<<std::endl;
                  fprintf(blah, "position moves %s\n",temp);
               }

               sharedData.clientBuffer.push_front(newMessage);
            }
            sharedData.clientCondition.notify_one();
         }

         if (turn != chessEngine.getTurn())
         {
            fprintf(blah,"go\n");
         }
         fflush(blah);
      }

      else
      {
         t_message newMessage;
         newMessage.id = PRESSED_BOARD_NOT_PLAYING;

         {
            boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

            sharedData.clientBuffer.push_front(newMessage);
            sharedData.clientCondition.notify_one();
         }
      }

      break;
   }

   case RECIEVE_PAWN_PROMOTE:
   {
      if (status  == PLAYING_TWO)
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
      }

      else
      {
         t_message newMessage;
         newMessage.id = PRESSED_BOARD_NOT_PLAYING;

         {
            boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

            sharedData.netBuffer.push_front(newMessage);
            sharedData.netCondition.notify_one();
         }
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


      if (status != NOTHING)
      {
         t_message newMessage;
         newMessage.id = RESET_WARNING_SINGLE;

         {
            boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

            sharedData.clientBuffer.push_front(newMessage);
            sharedData.clientCondition.notify_one();
         }
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

   case NEW_GAME_TWO:
   {
      std::cout<<"Cli is starting a new game for two"<<std::endl;

      t_message newMessage;
      newMessage.id = SET_GUI;
      {
         boost::unique_lock<boost::mutex> lock(sharedData.netMutex);

         sharedData.clientBuffer.push_front(newMessage);
         sharedData.clientCondition.notify_one();
      }

      status =  PLAYING_TWO;
      break;
   }

   case NEW_GAME_ONE:
   {
      std::cout<<"Cli is starting a new game for one"<<std::endl;

      t_message newMessage;
      newMessage.id = SET_GUI;
      {
         boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

         sharedData.clientBuffer.push_front(newMessage);
         sharedData.clientCondition.notify_one();
      }

      status =  PLAYING_ONE;

      if (pipe(in))
      {
         perror("Pipe has failed");
         exit(1);
      }

      boost::thread uciThread(boost::bind(createUci,boost::ref(sharedData),in[0],in[1]));
      
      blah = fdopen(in[1],"w");

      fprintf(blah,"uci\nucinewgame\nposition startpos\ngo\n");
      fflush(blah);


      break;
   }

   case UCI_RESPONSE:
   {
      if (status != PLAYING_ONE)
         break;

      std::cout<<"Resp: "<<message.uciResponse.response;

      char *temp = strdup(message.uciResponse.response);

      char *last;
      char *pch = strtok_r(temp," ",&last);
      if (!strcmp(pch,"bestmove"))
      {

         pch = strtok_r(NULL," ",&last);

         fprintf(blah,"position moves %s\n",pch);
         fflush(blah);

         t_myVector2 oldPos,pos;

         oldPos.x =  pch[0] - 'a';
         oldPos.y = '8' - pch[1];

         pos.x = pch[2] - 'a';
         pos.y = '8' - pch[3];

         t_message newMessage = chessEngine.insertMove(oldPos,pos);
      {
         boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

         sharedData.clientBuffer.push_front(newMessage);
         sharedData.clientCondition.notify_one();
      }
         std::cout<<"The positions are "<<oldPos<<" and "<<pos<<std::endl;
      }

      free(temp);


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
      std::cout<<"And I do not know what it was "<<message.id<<std::endl;

   }

   return 0;
}
