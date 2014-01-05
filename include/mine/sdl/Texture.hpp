#ifndef MINE_SDL_TEXTURE_HPP_INC
#define MINE_SDL_TEXTURE_HPP_INC

#include <SDL2/SDL.h>

#include <mine/goodies.hpp>

namespace mine
{
  namespace sdl
  {
    class Renderer;
    class Surface;
    class Texture
    {
      public:
        static Texture CreateFromSurface(const Renderer &, const Surface &);

        Texture(Texture&&);
        Texture& operator=(Texture&&);

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        ~Texture();

        SDL_Texture * getHandle() const
        { return m_texture; }

      private:
        Texture(SDL_Texture * texture);

        SDL_Texture * m_texture;
    };
  }
}

#endif
