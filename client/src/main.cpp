#include <iostream>
#include <vector>

#include "gui/chessGui.h"
#include "cli/chessCli.h"

#include "messages.h"

using std::vector;
using std::cout;
using std::endl;

int main(int argv, char **argc)
{
   t_sharedData sharedData;

   try
   {
      t_chessGui gui(sharedData);
      t_chessCli cli(sharedData);

      gui.run();
   }

   catch(std::exception &exception)
   {
      cout<<"Error: "<<exception.what();
      return -2;
   }

   return 0;
}
