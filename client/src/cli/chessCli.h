#ifndef CHESS_CLI_H_INCLUDED
#define CHESS_CLI_H_INCLUDED

#include <boost/utility.hpp>
#include <iostream>

#include <pantheios/inserters.hpp>
#include <pantheios/pantheios.hpp>

#define debug(X) pantheios::log(pantheios::debug,X)

class t_chessCli : boost::noncopyable
{
public:
   t_chessCli()
   {}
   
   ~t_chessCli()
   {
      debug("Exiting chessCli");  
   }

private:
};

#endif
