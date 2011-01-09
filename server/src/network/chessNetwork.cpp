#include "chessNetwork.h"
#include "chessConnection.h"
#include "../cli/chessCli.h"

#include "../messages.h"

#include <iostream>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

//namespace tcp = boost::asio::ip::tcp;
using namespace boost::asio::ip;

t_chessNetwork::t_chessNetwork()
{
}


void makeCli(t_sharedData &sharedData)
{
   t_chessCli cli(sharedData);

   cli.run();
}

void makeConnection(const boost::shared_ptr<tcp::socket> &socket)
{
   t_sharedData sharedData;

   boost::thread createCli(boost::bind(makeCli,boost::ref(sharedData)));
   t_chessConnection connection(sharedData,socket);
}

void t_chessNetwork::run()
{
   tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1510));

   while (1)
   {
      tcp::endpoint endpoint;
      boost::shared_ptr<tcp::socket> socket = boost::make_shared<tcp::socket>(io_service);
      acceptor.accept(*socket,endpoint);

      std::cout<<"I have recieved a connection at "<<endpoint<<std::endl;

      boost::thread connectThread(boost::bind(makeConnection,boost::cref(socket)));
   }


}
