#ifndef MINE_SDL_RENDERER_HPP_INC
#define MINE_SDL_RENDERER_HPP_INC

#include <SDL2/SDL.h>
#include <set>
#include <ostream>
#include <mine/goodies.hpp>
#include <mine/Rect.hpp>

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

        Pos getWindowSize() const
        { return m_winSize; }

        SDL_Renderer * getHandle() const
        { return m_renderer; }

        /**
         *  Clears the canvas.
         */
        void clear();

        /**
         * Copies the whole texture to the whole drawing canvas.
         */
        void copyAll(const Texture & texture);

        /**
         * Copies part of the texture to the whole canvas. Part is defined by source.
         */
        void copyFrom(const Texture & texture, const Rect & source);

        /**
         * Copies the whole texture to a defined part of the canvas.
         */
        void copyTo(const Texture & texture, const Rect & dest);

        /**
         * Shows the new canvas.
         */
        void present();

      private:
        SDL_Renderer * m_renderer;
        Pos m_winSize;
    };
  }
}

#endif
