#include <iostream>
#include <vector>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "gui/chessGui.h"
#include "cli/chessCli.h"
#include "net/chessNet.h"

#include "messages.h"

#include <gtkmm.h>

using std::vector;
using std::cout;
using std::endl;

void createCli(t_sharedData &sharedData)
{
   t_chessCli cli(sharedData);
   cli.run();
}

void createNet(t_sharedData &sharedData)
{
   t_chessNet net(sharedData);
   net.run();
}

int main(int argc, char **argv)
{
   Gtk::Main kit(argc,argv);

   t_sharedData sharedData;

   try
   {
      boost::thread cliThread(boost::bind(createCli,boost::ref(sharedData)));
      boost::thread netThread(boost::bind(createNet,boost::ref(sharedData)));
      t_chessGui gui(sharedData);

      gui.run();
      cliThread.join();
      netThread.join();
   }

   catch(std::exception &exception)
   {
      cout<<"Error: "<<exception.what();
      return -2;
   }

   return 0;
}
