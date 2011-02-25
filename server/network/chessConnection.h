#ifndef CHESS_CONNECTION_H_INCLUDED
#define CHESS_CONNECTION_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

class t_connectionData;
class t_sharedGame;
class t_myData;

class t_chessConnection : boost::noncopyable
{
public:
   t_chessConnection(boost::shared_ptr<t_connectionData> theSharedData, const boost::shared_ptr<boost::asio::ip::tcp::socket> &theSocket ,boost::asio::ip::tcp::endpoint end);

   void run();

   ~t_chessConnection()
   {
   }

private:

   void needToQuit(boost::system::error_code ecf);

   boost::shared_ptr<t_connectionData> connectionData;
   boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
   boost::asio::ip::tcp::endpoint end;

   bool color;
   bool playing;
  
   boost::shared_ptr<t_myData> myData;
   boost::shared_ptr<t_connectionData> partner;
   boost::shared_ptr<t_sharedGame> sharedGame;
   
};

#endif
