#ifndef MYVECTOR2_H_INCLUDED
#define MYVECTOR2_H_INCLUDED

#include <ostream>

struct t_myVector2
{
public:
   uint8_t x;
   uint8_t y;

   bool operator==(const t_myVector2 &vec) const
   {
      return ((x == vec.x) && (y == vec.y));
   }

   bool operator<(const t_myVector2 &vec) const
   {
      return (x*10 + y < vec.x * 10 + vec.y );
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
      out<<(int)vec.x<<' '<<(int)vec.y;
      
      return out;
   }
};


#endif
