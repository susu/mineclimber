#ifndef MINE_PIXELPOS_HPP_INC
#define MINE_PIXELPOS_HPP_INC

#include <ostream>

namespace mine
{
  struct PixelPos
  {
    int x;
    int y;
  };

  inline std::ostream& operator<<(std::ostream & out, const PixelPos & pos)
  {
    return out << "(" << pos.x << ", " << pos.y << ")";
  }
}

#endif
