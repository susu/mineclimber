#ifndef MINE_SDL_RENDERER_HPP_INC
#define MINE_SDL_RENDERER_HPP_INC

#include <SDL2/SDL.h>
#include <set>
#include <ostream>
#include <mine/goodies.hpp>

namespace mine
{
  namespace sdl
  {
    enum class RendererFlag : uint32_t
    {
      Software      = SDL_RENDERER_SOFTWARE,
      Accelerated   = SDL_RENDERER_ACCELERATED,
      PresentVSync  = SDL_RENDERER_PRESENTVSYNC,
      TargetTexture = SDL_RENDERER_TARGETTEXTURE,
    };
    std::ostream & operator<<(std::ostream& out, RendererFlag flag);

    class Window;
    class Texture;
    class Renderer : NonTransferable
    {
      public:
        Renderer(const Window & win, std::set<RendererFlag> renderFlags);
        ~Renderer();

        SDL_Renderer * getHandle() const
        { return m_renderer; }

        void clear();
        void copy(const Texture & texture);
        void present();

      private:
        SDL_Renderer * m_renderer;
    };
  }
}

#endif
