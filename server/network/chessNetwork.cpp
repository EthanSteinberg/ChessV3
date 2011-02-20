#include "chessNetwork.h"
#include "chessConnection.h"

#include "messages.h"

#include <iostream>

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "myDataBase.h"

//namespace tcp = boost::asio::ip::tcp;
using namespace boost::asio::ip;

t_chessNetwork::t_chessNetwork()
{
}

void makeConnection(const boost::shared_ptr<tcp::socket> &socket, boost::shared_ptr<t_myDataInfo> myDataInfo , tcp::endpoint end)
{
   boost::shared_ptr<t_connectionData>  connectionData= boost::make_shared<t_connectionData>(myDataInfo);
   t_chessConnection connection(connectionData,socket,end);
   connection.run();
}

void t_chessNetwork::run()
{
   tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1510));
   boost::shared_ptr<t_myDataInfo> myDataInfo = boost::make_shared<t_myDataInfo>();

   while (1)
   {
      tcp::endpoint endpoint;
      boost::shared_ptr<tcp::socket> socket = boost::make_shared<tcp::socket>(io_service);
      acceptor.accept(*socket,endpoint);

      std::cout<<"I have recieved a connection at "<<endpoint<<"  "<<socket->is_open()<<std::endl;

      boost::thread connectThread(boost::bind(makeConnection,socket,myDataInfo,endpoint));
   }


}
