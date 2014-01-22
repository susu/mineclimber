#ifndef MINE_RECT_HPP_INC
#define MINE_RECT_HPP_INC

#include <mine/Pos.hpp>

namespace mine
{
  struct Rect
  {
    Pos m_pos;       ///< upper left corner
    Pos m_dimension; ///< size

    Rect() {}
    Rect(Pos p, Pos d)
      : m_pos(p)
      , m_dimension(d)
    {}

    Rect(int x, int y, int dx, int dy)
      : m_pos(x,y)
      , m_dimension(dx, dy)
    {}
  };

  inline std::ostream& operator<<(std::ostream & out, const Rect & r)
  {
    return out << r.m_pos << "; " << r.m_dimension;
  }

  struct FRect
  {
    FPos m_pos;       ///< upper left corner
    FPos m_dimension; ///< size

    FRect() {}
    FRect(FPos p, FPos d)
      : m_pos(p)
      , m_dimension(d)
    {}

    FRect(double x, double y, double dx, double dy)
      : m_pos(x, y)
      , m_dimension(dx, dy)
    {}
  };

  inline std::ostream& operator<<(std::ostream & out, const FRect & r)
  {
    return out << r.m_pos << "; " << r.m_dimension;
  }
}

#endif
