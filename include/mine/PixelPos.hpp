#ifndef MINE_PIXELPOS_HPP_INC
#define MINE_PIXELPOS_HPP_INC

#include <ostream>

namespace mine
{
  struct PixelPos
  {
    int m_width;
    int m_height;
  };

  inline std::ostream& operator<<(std::ostream & out, const PixelPos & pos)
  {
    return out << "(" << pos.m_width << ", " << pos.m_height << ")";
  }
}

#endif
