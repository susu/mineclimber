#ifndef MINE_RECT_HPP_INC
#define MINE_RECT_HPP_INC

#include <mine/PixelPos.hpp>

namespace mine
{
  struct Rect
  {
    PixelPos m_pos;       ///< upper left corner
    PixelPos m_dimension; ///< size
  };
}

#endif
