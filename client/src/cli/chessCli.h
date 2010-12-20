#ifndef CHESS_CLI_H_INCLUDED
#define CHESS_CLI_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>

class t_sharedData;

class t_chessCli : boost::noncopyable
{
public:
   t_chessCli(t_sharedData &theSharedData);

   ~t_chessCli()
   {
   }

private:
    t_sharedData &sharedData;
};

#endif
