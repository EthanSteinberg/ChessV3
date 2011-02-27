#ifndef CHESS_UCI_H_INCLUDED
#define CHESS_UCI_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <bitset>

#include "myvector2.h"

#include "engine/chessEngine.h"


class t_sharedData;
class t_message;

class t_chessUci : boost::noncopyable
{
public:
   t_chessUci(t_sharedData &theSharedData, int fd1, int fd2);

   void run();

   ~t_chessUci()
   {
   }

private:

   int in[2];
   int out[2];

   t_sharedData &sharedData;

};
#endif
