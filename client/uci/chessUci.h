#ifndef CHESS_UCI_H_INCLUDED
#define CHESS_UCI_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>
#include <vector>
#include <set>
#include <bitset>

#include "myvector2.h"

#include "engine/chessEngine.h"
#include <string>


class t_sharedData;
class t_message;

class t_chessUci : boost::noncopyable
{
public:
   t_chessUci(t_sharedData &theSharedData, int fd1, int fd2, std::string filename);

   void run();

   ~t_chessUci()
   {
   }

private:

   t_sharedData &sharedData;
   std::string filename;
   int in[2];
   int out[2];


};
#endif
