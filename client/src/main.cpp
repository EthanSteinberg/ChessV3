#include <iostream>
#include <vector>

#include "gui/chessGui.h"
#include "cli/chessCli.h"

using std::vector;
using std::cout;
using std::endl;

int main(int argv, char **argc)
{
   try
   {
      t_chessGui gui;
      t_chessCli cli;

      gui.run();
   }

   catch(std::exception &exception)
   {
      cout<<"Error: "<<exception.what();
      return -2;
   }

   return 0;
}
