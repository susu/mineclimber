#ifndef MINE_PAINTER_HPP_INC
#define MINE_PAINTER_HPP_INC

namespace mine
{
  class BlockContainer;
  class ClipRenderer;

  class Painter
  {
    public:
      Painter(const BlockContainer & container, ClipRenderer & renderer);

    // private:
      const BlockContainer & m_container;
      ClipRenderer & m_renderer;
  };
}

#endif
