#ifndef MINE_SDL_CONTEXT_HPP_INC
#define MINE_SDL_CONTEXT_HPP_INC

#include <SDL2/SDL.h>
#include <set>

#include <mine/goodies.hpp>
#include <mine/Exceptions.hpp>

namespace mine
{
  namespace sdl
  {
    enum class SDLInitFlag : uint32_t
    {
      InitEverything = SDL_INIT_EVERYTHING,
    };

    inline std::ostream& operator<<(std::ostream & out, SDLInitFlag flag)
    {
      switch (flag)
      {
        case SDLInitFlag::InitEverything: return out << "InitEverything";
      }
      return out;
    }

    // RAII wrapper for SDL_Init
    class Context : NonTransferable
    {
      public:
        Context(std::set<SDLInitFlag> flags);
        ~Context();
    };
  }
}

#endif
