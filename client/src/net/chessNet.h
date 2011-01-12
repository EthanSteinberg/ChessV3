#ifndef CHESS_NET_H_INCLUDED
#define CHESS_NET_H_INCLUDED

#include "../messages.h"

class t_chessNet
{
public:
   t_chessNet(t_sharedData &theSharedData);

   void run();

private:
   t_sharedData &sharedData;
};


#endif
