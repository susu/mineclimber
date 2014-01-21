#ifndef MINE_CLIPRENDERER_HPP_INC
#define MINE_CLIPRENDERER_HPP_INC

#include <glm/glm.hpp>
#include <mine/goodies.hpp>
#include <mine/Rect.hpp>

namespace mine
{
  namespace sdl
  {
    class Renderer;
    class Texture;
  }
  class ClipRenderer : public NonTransferable
  {
    public:
      ClipRenderer(FRect startClip, sdl::Renderer & renderer);

      const FRect & getCurrentClip() const
      { return m_clip; }

      /**
       * Moves the current clip on X-axis with xDelta.
       * xDelta > 0: moves RIGHT
       * xDelta < 0: moves LEFT
       */
      void horizontalMove(double xDelta);

      /**
       * Moves the current clip on Y-axis with yDelta.
       * yDelta < 0: moves DOWN
       * yDelta > 0: moves UP
       */
      void verticalMove(double yDelta);

      void copy(const sdl::Texture & texture, const FRect & to);
    private:
      glm::mat3 m_viewMatrix;
      FRect m_clip;
      sdl::Renderer & m_renderer;
  };
}

#endif
