#ifndef MINE_CLIPRENDERER_HPP_INC
#define MINE_CLIPRENDERER_HPP_INC

#include <mine/goodies.hpp>
#include <mine/Rect.hpp>

namespace mine
{
  namespace sdl
  {
    class Renderer;
  }
  class ClipRenderer : public NonTransferable
  {
    public:
      ClipRenderer(Rect startClip, sdl::Renderer & renderer);

      const Rect & getCurrentClip() const
      { return m_clip; }

      /**
       * Moves the current clip on X-axis with xDelta.
       * xDelta > 0: moves RIGHT
       * xDelta < 0: moves LEFT
       */
      void horizontalMove(double xDelta);

      /**
       * Moves the current clip on Y-axis with yDelta.
       * yDelta > 0: moves DOWN
       * yDelat < 0: moves UP
       */
      void verticalMove(double yDelta);
    private:
      Rect m_clip;
      sdl::Renderer & m_renderer;
  };
}

#endif
