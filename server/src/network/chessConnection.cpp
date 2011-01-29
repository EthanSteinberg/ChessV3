#include "chessConnection.h"

#include "../messages.h"
#include <boost/shared_ptr.hpp>


using namespace boost::asio::ip;

t_chessConnection::t_chessConnection(t_sharedData &theSharedData, const boost::shared_ptr<tcp::socket> &theSocket ) : sharedData(theSharedData), socket(theSocket)
{
}

void t_chessConnection::run()
{

}
