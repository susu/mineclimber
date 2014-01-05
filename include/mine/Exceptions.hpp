#ifndef MINE_EXCEPTIONS_HPP_INC
#define MINE_EXCEPTIONS_HPP_INC

#include <stdexcept>
#include <sstream>
#include <mine/goodies.hpp>

#define MINE_RAISE(_extype,x) \
do {\
  std::ostringstream _os;\
  _os << x;\
  throw _extype(__FILE__,__LINE__,_os.str());\
} while(false)

namespace mine
{
  class MineException : public std::runtime_error
  {
    public:
      MineException(const std::string & msg)
        : std::runtime_error(msg)
      {}

      MineException(const char * file, int line, const std::string & msg)
        : std::runtime_error(MakeString() << "thrown at " << file <<
                             ":" << line << " message: '" << msg << "'")
      {}
  };

  class SDLException : public MineException
  {
    public:
      using MineException::MineException;
  };
}

#endif
