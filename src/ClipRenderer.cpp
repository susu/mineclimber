#include <mine/ClipRenderer.hpp>
#include <mine/sdl/Renderer.hpp>

using namespace mine;

ClipRenderer::ClipRenderer(Rect startClip, sdl::Renderer & renderer)
  : m_clip(startClip)
  , m_renderer(renderer)
{}

