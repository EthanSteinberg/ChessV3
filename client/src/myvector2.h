#ifndef MYVECTOR2_H_INCLUDED
#define MYVECTOR2_H_INCLUDED

#include <ostream>

struct t_myVector2
{
public:
   int x;
   int y;

   bool operator==(const t_myVector2 &vec) const
   {
      return ((x == vec.x) && (y == vec.y));
   }

   bool operator<(const t_myVector2 &vec) const
   {
      return ((x < vec.x) && (y < vec.y));
   }


   friend std::ostream &operator<<(std::ostream &out, const t_myVector2 &vec)
   {
      out<<vec.x<<' '<<vec.y;
      
      return out;
   }
};


#endif
