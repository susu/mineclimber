#ifndef MINE_ENFORCE_HPP_INC
#define MINE_ENFORCE_HPP_INC

#include <mine/goodies.hpp>
#include <mine/Exceptions.hpp>

#define ENFORCE(cond,msg)\
  enf::enforce<mine::MineException>((cond),__FILE__,__LINE__,\
      MakeString()<<"ENFORCE FAILED! "<< msg);

namespace enf
{
  template<class E, class... Arg>
  inline void enforce(bool condition, Arg&&... arg)
  {
    if (!condition)
    {
      throw E(std::forward<Arg>(arg)...);
    }
  }
}

#endif
