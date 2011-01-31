#ifndef CHESS_CONNECTION_H_INCLUDED
#define CHESS_CONNECTION_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

class t_connectionData;

class t_chessConnection : boost::noncopyable
{
public:
   t_chessConnection(t_connectionData &theSharedData, const boost::shared_ptr<boost::asio::ip::tcp::socket> &theSocket );

   void run();

   ~t_chessConnection()
   {
   }

private:
   t_connectionData &connectionData;
   boost::shared_ptr<boost::asio::ip::tcp::socket> socket;
};

#endif
