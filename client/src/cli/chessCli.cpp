#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>

#include "chessCli.h"
#include "../messages.h"

t_chessCli::t_chessCli(t_sharedData &theSharedData) : sharedData(theSharedData), selected(0)
{
   std::cout<<"Hello world"<<std::endl;

   board =
   {
      {10, 11, 12, 14, 13, 12, 11, 10},
      { 9,  9,  9,  9,  9,  9,  9,  9},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 0,  0,  0,  0,  0,  0,  0,  0},
      { 1,  1,  1,  1,  1,  1,  1,  1},
      { 2,  3,  4,  6,  5,  4,  3,  2}
   };

}

void t_chessCli::run()
{
   for (;;)
   {
      t_message message;

      {
         boost::unique_lock<boost::mutex> lock(sharedData.gameMutex);

         if (sharedData.gameBuffer.empty())
         {
            sharedData.gameCondition.wait(lock);
         }

         message = sharedData.gameBuffer.back();
         sharedData.gameBuffer.pop_back();

      }

      std::cout<<"I have recieved a message"<<std::endl;

      switch (message.id)
      {

      case BOARD_CLICKED:
      {
         t_myVector2 pos = message.boardClicked.pos;
         std::cout<<"It was clicked at "<<pos<<std::endl;

         t_message newMessage;
         newMessage.id = HIGHLIGHT_SPACE;


         if (selected)
         {
            if (pos == selectedPos)
            {
               selected = 0;
               newMessage.highlightSpace.pos = selectedPos;
               newMessage.highlightSpace.color = 0;
               {
                  boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

                  sharedData.clientBuffer.push_front(newMessage);

                  for (auto iter = move.begin(); iter != move.end(); iter++)
                  {
                     newMessage.highlightSpace.pos = *iter;
                     newMessage.highlightSpace.color = 0;

                     sharedData.clientBuffer.push_front(newMessage);
                  }

                  for (auto iter = hit.begin(); iter != hit.end(); iter++)
                  {
                     newMessage.highlightSpace.pos = *iter;
                     newMessage.highlightSpace.color = 0;

                     sharedData.clientBuffer.push_front(newMessage);
                  }
               }

               move.clear();
               hit.clear();
            }

            else if (std::find(move.begin(), move.end(), pos) != move.end())
            {
               selected = 0;
               newMessage.highlightSpace.pos = selectedPos;
               newMessage.highlightSpace.color = 0;
               
               {
                  boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

                  sharedData.clientBuffer.push_front(newMessage);

                  for (auto iter = move.begin(); iter != move.end(); iter++)
                  {
                     newMessage.highlightSpace.pos = *iter;
                     newMessage.highlightSpace.color = 0;

                     sharedData.clientBuffer.push_front(newMessage);
                  }

                  for (auto iter = hit.begin(); iter != hit.end(); iter++)
                  {
                     newMessage.highlightSpace.pos = *iter;
                     newMessage.highlightSpace.color = 0;

                     sharedData.clientBuffer.push_front(newMessage);
                  }

                  newMessage.id = MOVE_PIECE;
                  newMessage.movePiece.pos = pos;
                  newMessage.movePiece.oldPos = selectedPos;

                  sharedData.clientBuffer.push_front(newMessage);
               }

               move.clear();
               hit.clear();

               board[pos.y][pos.x] = board[selectedPos.y][selectedPos.x];
               board[selectedPos.y][selectedPos.x] = 0;
            }

            else if (std::find(hit.begin(), hit.end(), pos) != hit.end())
            {
               selected = 0;
               newMessage.highlightSpace.pos = selectedPos;
               newMessage.highlightSpace.color = 0;
               
               {
                  boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

                  sharedData.clientBuffer.push_front(newMessage);

                  for (auto iter = move.begin(); iter != move.end(); iter++)
                  {
                     newMessage.highlightSpace.pos = *iter;
                     newMessage.highlightSpace.color = 0;

                     sharedData.clientBuffer.push_front(newMessage);
                  }

                  for (auto iter = hit.begin(); iter != hit.end(); iter++)
                  {
                     newMessage.highlightSpace.pos = *iter;
                     newMessage.highlightSpace.color = 0;

                     sharedData.clientBuffer.push_front(newMessage);
                  }

                  newMessage.id = CAPTURE_PIECE;
                  newMessage.movePiece.pos = pos;
                  newMessage.movePiece.oldPos = selectedPos;

                  sharedData.clientBuffer.push_front(newMessage);
               }

               move.clear();
               hit.clear();

               board[pos.y][pos.x] = board[selectedPos.y][selectedPos.x];
               board[selectedPos.y][selectedPos.x] = 0;
            }


         }

         else if (board[pos.y][pos.x])
         {
            selected = 1;
            selectedPos = pos;
            newMessage.highlightSpace.pos = pos;
            newMessage.highlightSpace.color = 1;

            generateMoves(pos);

            {
               boost::unique_lock<boost::mutex> lock(sharedData.clientMutex);

               sharedData.clientBuffer.push_front(newMessage);

               for (auto iter = move.begin(); iter != move.end(); iter++)
               {
                  newMessage.highlightSpace.pos = *iter;
                  newMessage.highlightSpace.color = 2;

                  sharedData.clientBuffer.push_front(newMessage);
               }

               for (auto iter = hit.begin(); iter != hit.end(); iter++)
               {
                  newMessage.highlightSpace.pos = *iter;
                  newMessage.highlightSpace.color = 3;

                  sharedData.clientBuffer.push_front(newMessage);
               }

            }


         }



         break;
      }

      case QUIT_MESSAGE:
         std::cout<<"It told me to quit"<<std::endl;
         return;

      default:
         std::cout<<"And I do not know what it was"<<std::endl;

      }
   }
}




