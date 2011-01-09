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
      return (x*x + y*y < vec.x * vec.x + vec.y * vec.y);
   }

   t_myVector2 operator-(const t_myVector2 &vec) const
   {
      t_myVector2 out;

      out.x = x - vec.x;
      out.y = y - vec.y;

      return out;
   }


   friend std::ostream &operator<<(std::ostream &out, const t_myVector2 &vec)
   {
      out<<vec.x<<' '<<vec.y;
      
      return out;
   }
};


#endif
