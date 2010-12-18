#ifndef CHESS_GUI_H_INCLUDED
#define CHESS_GUI_H_INCLUDED

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include "chessCegui.h"

class t_chessGui : boost::noncopyable
{
public:
   t_chessGui() 
   {}

   void run();
         
private:
   t_chessCegui chessCegui;
};

#endif
