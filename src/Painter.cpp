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
  LOG_DEBUG("Drawing block: ", block);
}

void Painter::drawBlocks()
{
  // TODO: compute visible block coordinates

}
