#ifndef MY_DATA_BASE_INCLUDED
#define MY_DATA_BASE_INCLUDED

#include <string>
#include <map>
#include <boost/asio.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include "messages.h"

enum {NOTHING, PLAYING};


struct t_myData
{
   std::string name;
   int wins;
   int losses;
   int status;

   boost::weak_ptr<t_connectionData> connectionData;
};

typedef std::map<boost::asio::ip::tcp::endpoint, boost::shared_ptr<t_myData> > t_myDataBase;


struct t_myDataInfo
{
   t_myDataBase myDataBase;
   boost::shared_mutex myDataMutex;
};


#endif
