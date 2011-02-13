#ifndef CHESS_CONNECTION_H_INCLUDED
#define CHESS_CONNECTION_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

class t_connectionData;
class t_sharedGame;

class t_chessConnection : boost::noncopyable
{
public:
   t_chessConnection(boost::shared_ptr<t_connectionData> theSharedData, const boost::shared_ptr<boost::asio::ip::tcp::socket> &theSocket ,boost::asio::ip::tcp::endpoint end);

   void run();

   ~t_chessConnection()
   {
   }

private:

   boost::shared_ptr<t_connectionData> connectionData;
   boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
   boost::asio::ip::tcp::endpoint end;

   bool playing;

   boost::shared_ptr<t_connectionData> partner;
   boost::shared_ptr<t_sharedGame> sharedGame;
   
};

#endif
