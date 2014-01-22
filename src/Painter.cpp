#include <mine/Painter.hpp>
#include <cmath>
#include <mine/BlockContainer.hpp>
#include <mine/ClipRenderer.hpp>
#include <mine/Logger.hpp>
#include <mine/SoilBlock.hpp>

using namespace mine;

Painter::Painter(BlockContainer & container, ClipRenderer & renderer, sdl::Texture && texture)
  : m_container(container)
  , m_renderer(renderer)
  , m_texture(std::move(texture))
{}

void Painter::visit(const SoilBlock & block)
{
  const auto & pos = block.getPos();
  m_renderer.copy(m_texture, FRect(pos.x, pos.y, 1.0, 1.0));
}

void Painter::drawBlocks()
{
  // TODO: compute visible block coordinates
  FRect clip = m_renderer.getCurrentClip();
  int xMin = floor(clip.m_pos.x);
  int xMax = ceil(clip.m_pos.x + clip.m_dimension.x + 1);

  int yMin = floor(clip.m_pos.y);
  int yMax = ceil(clip.m_pos.y + clip.m_dimension.y + 1);

  for (int x = xMin; x < xMax; ++x)
  {
    for(int y = yMin; y < yMax; ++y)
    {
      Block * block = m_container.getBlock(x, y);
      if (block != nullptr)
        block->accept(*this);
    }
  }
}
