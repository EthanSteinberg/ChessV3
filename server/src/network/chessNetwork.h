#ifndef CHESS_NETWORK_H_INCLUDED
#define CHESS_NETWORK_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>

class t_chessNetwork : boost::noncopyable
{
public:
   t_chessNetwork();

   void run();

   ~t_chessNetwork()
   {
   }

private:
};

#endif
