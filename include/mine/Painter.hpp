#ifndef MINE_PAINTER_HPP_INC
#define MINE_PAINTER_HPP_INC

#include <mine/BlockVisitor.hpp>
#include <mine/sdl/Texture.hpp>

namespace mine
{
  class BlockContainer;
  class ClipRenderer;

  // the name 'Drawer' was too boring.
  class Painter : public BlockVisitor
  {
    public:
      Painter(BlockContainer & container, ClipRenderer & renderer, sdl::Texture && tx);

      void drawBlocks();

      void visit(const SoilBlock & block) override;

      // TODO private
    protected:
      BlockContainer & m_container;
      ClipRenderer & m_renderer;
      sdl::Texture m_texture;
  };
}

#endif
