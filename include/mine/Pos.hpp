#ifndef MINE_PIXELPOS_HPP_INC
#define MINE_PIXELPOS_HPP_INC

#include <ostream>
#include <glm/glm.hpp>

namespace mine
{
  struct Pos
  {
    int x;
    int y;

    Pos() : x(0), y(0) {}
    Pos(int x_, int y_) : x(x_), y(y_) {}

    operator glm::vec3() const
    { return glm::vec3(x, y, 1); }

    Pos& operator=(const glm::vec3& v)
    {
      x = v.x;
      y = v.y;
      return *this;
    }
  };

  inline bool operator==(const Pos& lhs, const Pos& rhs)
  {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  inline std::ostream& operator<<(std::ostream & out, const Pos & pos)
  {
    return out << "(" << pos.x << ", " << pos.y << ")";
  }

  struct FPos
  {
    double x;
    double y;
    FPos() : x(0), y(0) {}
    FPos(double x_, double y_) : x(x_), y(y_) {}

    operator glm::vec3() const
    { return glm::vec3(x, y, 1); }
  };

  inline std::ostream& operator<<(std::ostream & out, const FPos & pos)
  {
    return out << "(" << pos.x << ", " << pos.y << ")";
  }
}

#endif
