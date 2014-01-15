#include <mine/Painter.hpp>

using namespace mine;

Painter::Painter(const BlockContainer & container, ClipRenderer & renderer)
  : m_container(container)
  , m_renderer(renderer)
{}

