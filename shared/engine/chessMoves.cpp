#include <iostream>

#include <boost/thread.hpp>

#include <cstdio>
#include <cstdlib>

#include "chessEngine.h"
#include "messages.h"

void t_chessEngine::moveMove(t_myVector2 pos, std::vector<t_message> &buffer)
{
   t_message newMessage;

   if (boost::optional<t_myVector2> temp = checkCheck(pos,selectedPos))
   {
      newMessage.id = IN_CHECK;
      newMessage.inCheck.attackingPiece = temp.get();
      buffer.push_back(newMessage);
      std::cout<<"I am in check"<<std::endl;
      return;
   }

   if (turn == 0)
   {
      whitePieces.erase(selectedPos);
      whitePieces.insert(pos);
   }

   else
   {
      blackPieces.erase(selectedPos);
      blackPieces.insert(pos);
   }

   removeCastle(pos,selectedPos);

   clearHighlights(buffer);

   newMessage.id = MOVE_PIECE;
   newMessage.movePiece.pos = pos;
   newMessage.movePiece.oldPos = selectedPos;

   buffer.push_back(newMessage);

   board[pos.y][pos.x] = board[selectedPos.y][selectedPos.x];
   board[selectedPos.y][selectedPos.x] = 0;

   turn = !turn;

   if (checkCheckmate())
   {
      newMessage.id = CHECK_MATE;
      newMessage.checkMate.winner = !turn;
      buffer.push_back(newMessage);
      std::cout<<"I win"<<std::endl;
   }

}


void t_chessEngine::attackMove(t_myVector2 pos, std::vector<t_message> &buffer)
{
   t_message newMessage;

   if (boost::optional<t_myVector2> temp = checkCheck(pos,selectedPos))
   {
      newMessage.id = IN_CHECK;
      newMessage.inCheck.attackingPiece = temp.get();
      buffer.push_back(newMessage);
      std::cout<<"I am in check"<<std::endl;
      return;
   }

   if (turn == 0)
   {
      whitePieces.erase(selectedPos);
      whitePieces.insert(pos);

      blackPieces.erase(pos);
   }

   else
   {
      blackPieces.erase(selectedPos);
      blackPieces.insert(pos);

      whitePieces.erase(pos);
   }

   removeCastle(pos,selectedPos);

   clearHighlights(buffer);

   newMessage.id = CAPTURE_PIECE;
   newMessage.movePiece.pos = pos;
   newMessage.movePiece.oldPos = selectedPos;

   buffer.push_back(newMessage);

   board[pos.y][pos.x] = board[selectedPos.y][selectedPos.x];
   board[selectedPos.y][selectedPos.x] = 0;

   turn = !turn;

   if (checkCheckmate())
   {
      newMessage.id = CHECK_MATE;
      newMessage.checkMate.winner = !turn;
      buffer.push_back(newMessage);
      std::cout<<"I win"<<std::endl;
   }
}
void t_chessEngine::castleMove(t_myVector2 pos, std::vector<t_message> &buffer)
{
   t_message newMessage;


   t_myVector2 temp2;
   temp2.y = pos.y;

   for (temp2.x = pos.x; temp2.x != selectedPos.x; temp2.x += ((selectedPos.x - pos.x)/ labs(selectedPos.x - pos.x)))
   {
      if (boost::optional<t_myVector2>  temp = checkCheck(temp2,selectedPos))
      {
         newMessage.id = IN_CHECK;
         newMessage.inCheck.attackingPiece = temp.get();
         buffer.push_back(newMessage);
         std::cout<<"I am in check"<<std::endl;
         return;
      }
   }

   if (boost::optional<t_myVector2>  temp = checkCheck(selectedPos,selectedPos))
   {
      newMessage.id = IN_CHECK;
      newMessage.inCheck.attackingPiece = temp.get();
      buffer.push_back(newMessage);
      std::cout<<"I am in check"<<std::endl;
      return;
   }

   if (turn == 0)
   {
      whitePieces.erase(selectedPos);
      whitePieces.insert(pos);
   }

   else
   {
      blackPieces.erase(selectedPos);
      blackPieces.insert(pos);
   }

   removeCastle(pos,selectedPos);

   clearHighlights(buffer);

   newMessage.id = MOVE_PIECE;
   newMessage.movePiece.pos = pos;
   newMessage.movePiece.oldPos = selectedPos;

   buffer.push_back(newMessage);

   if (pos.x == 2) //left castle
   {
      newMessage.movePiece.pos.x = 3;
      newMessage.movePiece.oldPos.x = 0;
   }

   else
   {
      newMessage.movePiece.pos.x = 5;
      newMessage.movePiece.oldPos.x = 7;
   }

   buffer.push_back(newMessage);

   board[pos.y][pos.x] = board[selectedPos.y][selectedPos.x];
   board[selectedPos.y][selectedPos.x] = 0;

   if (pos.x == 2) //left
   {
      pos.x = 3;
      selectedPos.x = 0;

      board[pos.y][3] = board[selectedPos.y][0];
      board[selectedPos.y][0] = 0;
   }

   else
   {
      pos.x = 5;
      selectedPos.x = 7;

      board[pos.y][5] = board[selectedPos.y][7];
      board[selectedPos.y][7] = 0;
   }

   if (turn == 0)
   {
      whitePieces.erase(selectedPos);
      whitePieces.insert(pos);
   }

   else
   {
      blackPieces.erase(selectedPos);
      blackPieces.insert(pos);
   }

   turn = !turn;


   if (checkCheckmate())
   {
      newMessage.id = CHECK_MATE;
      newMessage.checkMate.winner = !turn;
      buffer.push_back(newMessage);
      std::cout<<"I win"<<std::endl;
   }

}

void t_chessEngine::promoteMove(t_myVector2 pos, std::vector<t_message> &buffer)
{
   t_message newMessage;

   if (boost::optional<t_myVector2> temp = checkCheck(pos,selectedPos))
   {
      newMessage.id = IN_CHECK;
      newMessage.inCheck.attackingPiece = temp.get();
      buffer.push_back(newMessage);
      std::cout<<"I am in check"<<std::endl;
      return;
   }

   if (turn == 0)
   {
      whitePieces.erase(selectedPos);
      whitePieces.insert(pos);
   }

   else
   {
      blackPieces.erase(selectedPos);
      blackPieces.insert(pos);
   }

   removeCastle(pos,selectedPos);

   clearHighlights(buffer);

   newMessage.id = MOVE_PIECE;
   newMessage.movePiece.pos = pos;
   newMessage.movePiece.oldPos = selectedPos;

   buffer.push_back(newMessage);

   newMessage.id = SHOW_PAWN_PROMOTE;
   newMessage.showPawnPromote.color = turn;

   buffer.push_back(newMessage);

   board[pos.y][pos.x] = board[selectedPos.y][selectedPos.x];
   board[selectedPos.y][selectedPos.x] = 0;

   pawnPos = pos;

   inPawnPromotion = 1;

}

void t_chessEngine::finishPromote(int type, std::vector<t_message> &buffer)
{
   t_message newMessage;
   newMessage.id = HIGHLIGHT_SPACE;

   newMessage.highlightSpace.pos = pawnPos;
   newMessage.highlightSpace.color = 0;

   buffer.push_back(newMessage);
   
   newMessage.id = CHANGE_ICON;
   newMessage.changeIcon.type = type;
   newMessage.changeIcon.pawnPos = pawnPos;

   buffer.push_back(newMessage);

   board[pawnPos.y][pawnPos.x] =  type + turn * 8;

   inPawnPromotion = 0;

   turn = !turn;

   if (checkCheckmate())
   {
      newMessage.id = CHECK_MATE;
      newMessage.checkMate.winner = !turn;
      buffer.push_back(newMessage);
      std::cout<<"I win"<<std::endl;
   }
   
}

void t_chessEngine::clearHighlights(std::vector<t_message> &buffer)
{
   t_message newMessage;
   newMessage.id = HIGHLIGHT_SPACE;

   selected = 0;
   newMessage.highlightSpace.pos = selectedPos;
   newMessage.highlightSpace.color = 0;

   {

      buffer.push_back(newMessage);

      for (auto iter = move.begin(); iter != move.end(); iter++)
      {
         newMessage.highlightSpace.pos = *iter;
         newMessage.highlightSpace.color = 0;

         buffer.push_back(newMessage);
      }

      for (auto iter = hit.begin(); iter != hit.end(); iter++)
      {
         newMessage.highlightSpace.pos = *iter;
         newMessage.highlightSpace.color = 0;

         buffer.push_back(newMessage);
      }

      for (auto iter = castle.begin(); iter != castle.end(); iter++)
      {
         newMessage.highlightSpace.pos = *iter;
         newMessage.highlightSpace.color = 0;

         buffer.push_back(newMessage);
      }

      for (auto iter = pawnPromote.begin(); iter != pawnPromote.end(); iter++)
      {
         newMessage.highlightSpace.pos = *iter;
         newMessage.highlightSpace.color = 0;

         buffer.push_back(newMessage);
      }

   }

   move.clear();
   hit.clear();
   castle.clear();
   pawnPromote.clear();


}
