#ifndef MINE_RECT_HPP_INC
#define MINE_RECT_HPP_INC

#include <mine/Pos.hpp>

namespace mine
{
  struct Rect
  {
    Pos m_pos;       ///< upper left corner
    Pos m_dimension; ///< size
  };
}

#endif
