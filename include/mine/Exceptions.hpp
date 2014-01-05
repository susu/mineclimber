#ifndef MINE_EXCEPTIONS_HPP_INC
#define MINE_EXCEPTIONS_HPP_INC

#include <stdexcept>
#include <sstream>

#define MINE_RAISE(_extype,x) \
do {\
  std::ostringstream _os;\
  _os << x;\
  throw _extype(_os.str());\
} while(false)

namespace mine
{
  class MineException : public std::runtime_error
  {
    public:
      MineException(const std::string & msg)
        : std::runtime_error(msg)
      {}
  };
}

#endif
