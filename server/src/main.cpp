#include <iostream>
#include <vector>

#include "network/chessNetwork.h"

using std::vector;
using std::cout;
using std::endl;

int main(int argv, char **argc)
{
   try
   {
      t_chessNetwork network;

      network.run();
   }

   catch(std::exception &exception)
   {
      cout<<"Error: "<<exception.what();
      return -2;
   }

   return 0;
}
