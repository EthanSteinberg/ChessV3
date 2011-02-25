#include "chessNet.h"

#include "messages.h"
#include "netMessages.h"

#include <iostream>

#include <string>

using namespace boost::asio::ip;

bool t_chessNet::connected(const std::string &name, const std::string &address)
{
   tcp::resolver resolver(io_service);
   tcp::resolver::query query(tcp::v4(), address, "1510");
   tcp::resolver::iterator iterator = resolver.resolve(query);

   boost::system::error_code ec;

   socket.connect(*iterator,ec);

   if (ec)
   {

      if (ec.value() == boost::system::errc::connection_refused)
      {
            std::cout<<"Connection fail"<<std::endl;

            t_message message;
            message.id = CONNECTION_NO_SERVER;


            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         return 0;
      }

      else
      {
         std::cout<<ec.message()<<std::endl;
         std::cout<<ec.value()<<std::endl;

         exit(1);
      }
   }

   t_netMessage newNetMessage;
   newNetMessage.id = NET_JOIN_SERVER;
   strcpy(newNetMessage.netJoinServer.name,name.c_str());

   boost::system::error_code ecf;
   boost::asio::write(socket,boost::asio::buffer(&newNetMessage,sizeof(newNetMessage)),boost::asio::transfer_all(),ecf);

   if (ecf)
   {
      bailOut(ecf);
      return 0;
   }

   for (;;)
   {
      // socket.send(boost::asio::buffer(&newNetMessage,sizeof(newNetMessage)));
      for (;;)
      {

         t_message message;
         {
            boost::unique_lock<boost::mutex> lock(sharedData.netMutex);

            if (sharedData.netBuffer.empty())
            {
               break;
            }

            message = sharedData.netBuffer.back();
            sharedData.netBuffer.pop_back();
         }
         std::cout<<"I have recieved a message"<<std::endl;

         switch (message.id)
         {
         case JOIN_SERVER:
         {
            std::cout<<"The name was: "<<message.joinServer.name<<" at a port of: , but I am already connected"<<message.joinServer.address<<std::endl;
            break;
         }

         case WANT_REFRESH_CONNECTION:
         {
            std::cout<<"Net has to send the want for connection data over the interwebs"<<std::endl;

            t_netMessage aNewNetMessage;
            aNewNetMessage.id = NET_REFRESH_CONNECTION;

            boost::asio::write(socket,boost::asio::buffer(&aNewNetMessage,sizeof(aNewNetMessage)),boost::asio::transfer_all(),ecf);
            
            if (ecf)
            {
               bailOut(ecf);
               return 0;
            }

            break;
         }

         case WANT_TO_PLAY_WITH:
         {
            std::cout<<"Net wants to play with a person"<<std::endl;

            t_netMessage aNewNetMessage;
            aNewNetMessage.id =  NET_WANT_TO_PLAY_WITH;

            strcpy (aNewNetMessage.netWantToPlayWith.name,message.wantToPlayWith.name);
            boost::asio::write(socket,boost::asio::buffer(&aNewNetMessage,sizeof(aNewNetMessage)),boost::asio::transfer_all(),ecf);

            if (ecf)
            {
               bailOut(ecf);
               return 0;
            }
            break;
         }

         case BOARD_CLICKED:
         {
            std::cout<<"Net telling the server that the board was clicked"<<std::endl;

            t_netMessage aNewNetMessage;
            aNewNetMessage.id =  NET_BOARD_CLICKED;
            aNewNetMessage.netBoardClicked.pos = message.boardClicked.pos;

            boost::asio::write(socket,boost::asio::buffer(&aNewNetMessage,sizeof(aNewNetMessage)),boost::asio::transfer_all(),ecf);

            if (ecf)
            {
               bailOut(ecf);
               return 0;
            }

            break;
         }

         case PLAY_RESPONSE:
         {
            std::cout<<"I have gotten a response from the request"<<std::endl;

            t_netMessage aNewNetMessage;
            aNewNetMessage.id =  NET_PLAY_RESPONSE;
            
            aNewNetMessage.netPlayResponse.response = message.playResponse.response;

            strcpy (aNewNetMessage.netPlayResponse.name,message.playResponse.name);
            boost::asio::write(socket,boost::asio::buffer(&aNewNetMessage,sizeof(aNewNetMessage)),boost::asio::transfer_all(),ecf);

            if (ecf)
            {
               bailOut(ecf);
               return 0;
            }

            break;
         }

         case DISCONNECT_MESSAGE:
         {
            std::cout<<"I was told to disconnect"<<std::endl;

            t_netMessage aNewNetMessage;
            aNewNetMessage.id = NET_QUIT_MESSAGE;

            boost::asio::write(socket,boost::asio::buffer(&aNewNetMessage,sizeof(aNewNetMessage)),boost::asio::transfer_all(),ecf);
            socket.close();

            return 0;
         }

         case QUIT_MESSAGE:
         {
            std::cout<<"It told me to quit"<<std::endl;

            t_netMessage aNewNetMessage;
            aNewNetMessage.id = NET_QUIT_MESSAGE;

            boost::asio::write(socket,boost::asio::buffer(&aNewNetMessage,sizeof(aNewNetMessage)),boost::asio::transfer_all(),ecf);

            return 1;
         }
         default:
            std::cout<<"And I do not know what it was"<<std::endl;
         }
      }

      for (;;)
      {
         if (!socket.available(ecf))
         {
            if (ecf != 0)
            {
            std::cout<<"I have an error for you "<<ecf.message()<<ecf<<std::endl;
            exit(0);
            }
            break;
         }

         t_netMessage netMessage;

         socket.read_some(boost::asio::buffer(&netMessage,sizeof(netMessage)));

         switch (netMessage.id)
         {

         case NET_PLAY_REQUEST:
         {
            std::cout<<"Someone wants to play with me "<<netMessage.netPlayRequest.name<<std::endl;

            t_message message;
            
            message.id = PLAY_REQUEST;
            strcpy(message.playRequest.name,netMessage.netPlayRequest.name);

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }
            sharedData.gameCondition.notify_one();

            break;
         }

         case NET_PLAY_ACCEPTED:
         {
            std::cout<<"play accepted "<<netMessage.netPlayRequest.name<<std::endl;

            t_message message;
            
            message.id = PLAY_ACCEPTED;

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }
            sharedData.gameCondition.notify_one();

            break;
         }
         case NET_PLAY_REJECTED:
         {
            std::cout<<"play rejected "<<netMessage.netPlayRequest.name<<std::endl;

            t_message message;
            
            message.id = PLAY_REJECTED;

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }
            sharedData.gameCondition.notify_one();

            break;
         }

         case NET_REFRESH_CONNECTION:
         {
            t_message message;

            message.id = REFRESH_CONNECTION;
            strcpy(message.refreshConnection.server,address.c_str());

            t_dataPacket dataPacket;

            std::cout<<"And the names come in: "<<std::endl;

            for (int i = 0; i<netMessage.netRefreshConnection.numOfPackets; i++)
            {
               socket.read_some(boost::asio::buffer(&dataPacket,sizeof(dataPacket)));
               std::cout<<dataPacket.name<<std::endl;

               message.dataPackets.push_back(dataPacket);
            }

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         }
         break;

         case NET_CONNECTION_SUCCESS:
         {
            std::cout<<"Connection success"<<std::endl;

            t_message message;
            message.id = CONNECTION_SUCCESS;


            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         break;
         }

         case NET_HIGHLIGHT_SPACE:
         {
            std::cout<<"net highlight space"<<std::endl;

            t_message message;
            message.id = HIGHLIGHT_SPACE;
            message.highlightSpace.pos = netMessage.netHighlightSpace.pos;
            message.highlightSpace.color = netMessage.netHighlightSpace.color;

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         break;
         }

         case NET_MOVE_PIECE:
         {
            std::cout<<"net highlight space"<<std::endl;

            t_message message;
            message.id = MOVE_PIECE;
            message.movePiece.pos = netMessage.netMovePiece.pos;
            message.movePiece.oldPos = netMessage.netMovePiece.oldPos;

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         break;
         }

         case NET_CAPTURE_PIECE:
         {
            std::cout<<"net highlight space"<<std::endl;

            t_message message;
            message.id = CAPTURE_PIECE;
            message.movePiece.pos = netMessage.netMovePiece.pos;
            message.movePiece.oldPos = netMessage.netMovePiece.oldPos;

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         break;
         }

         case NET_CHECK_MATE:
         {
            std::cout<<"net check mate"<<std::endl;

            t_message message;
            message.id = CHECK_MATE;
            message.checkMate.winner = netMessage.netCheckMate.winner;

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         break;
         }

         case NET_IN_CHECK:
         {
            std::cout<<"net in check"<<std::endl;

            t_message message;
            message.id = IN_CHECK;
            message.inCheck.attackingPiece = netMessage.netInCheck.attackingPiece;;

            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
         break;
         }

         case NET_CONNECTION_BAD_NAME:
         {
            std::cout<<"Connection bad name"<<std::endl;

            t_message message;
            message.id = CONNECTION_BAD_NAME;


            {
               boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

               sharedData.gameBuffer.push_front(message);
            }

            sharedData.gameCondition.notify_one();
            socket.close();
         }
         return 0;

         case NET_QUIT_MESSAGE:
            std::cout<<"It told me to quit"<<std::endl;
            return 1;

         default:
            std::cout<<"And I do not know what it was"<<std::endl;
         }
      }
   }

}

void t_chessNet::bailOut(boost::system::error_code ecf)
{
   std::cout<<"I have recieved the error "<<ecf.message()<<" and "<<ecf<<std::endl;
   socket.close();
}
