#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED

#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>

struct t_message
{
   int id;
};

typedef boost::circular_buffer<t_message> t_messageBuffer;

struct t_sharedData
{
   boost::mutex clientServerMutex;
   boost::mutex clientGameMutex;

   boost::condition_variable clientServerCondition;
   boost::condition_variable clientGameCondition;

   t_messageBuffer clientServerBuffer;
   t_messageBuffer clientGameBuffer;
};

#endif
