#ifndef CHESS_NET_H_INCLUDED
#define CHESS_NET_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <bitset>

#include <boost/asio.hpp>

#include "myvector2.h"


class t_sharedData;

class t_chessNet : boost::noncopyable
{
public:
   t_chessNet(t_sharedData &theSharedData);

   void run();
   void connected(const std::string &name,const std::string &address);

   ~t_chessNet()
   {
   }

private:

   t_sharedData &sharedData;

   boost::asio::io_service io_service;
   boost::asio::ip::tcp::socket socket; 

};

#endif
