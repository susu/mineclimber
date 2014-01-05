#ifndef MINE_SDL_SURFACE_HPP_INC
#define MINE_SDL_SURFACE_HPP_INC

#include <SDL2/SDL.h>
#include <mine/goodies.hpp>
#include <mine/Enforce.hpp>

namespace mine
{
  namespace sdl
  {
    class Surface
    {
      public:
        static Surface CreateFromPNG(const std::string path);
        ~Surface();

        Surface(Surface&& other);
        Surface& operator=(Surface&& other);

        Surface(const Surface&) = delete;
        Surface& operator=(const Surface&) = delete;

        SDL_Surface * getHandle() const
        {
          ENFORCE(m_surface, "Handle deleted!");
          return m_surface;
        }

      private:
        Surface(SDL_Surface * surface);

        SDL_Surface * m_surface;
    };
  }
}

#endif
