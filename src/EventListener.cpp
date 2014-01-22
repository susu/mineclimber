#include <mine/EventListener.hpp>
#include <mine/Logger.hpp>
#include <mine/sdl/events.hpp>
#include <mine/ClipRenderer.hpp>

using namespace mine;


EventListener::EventListener(ClipRenderer & renderer)
  : m_renderer(renderer)
{}

void EventListener::visit(const sdl::KeyEvent & ev)
{
  LOG_DEBUG("KeyEvent arrived: ", ev);
  switch (ev.GetKeycode())
  {
    case SDLK_UP:
      m_renderer.verticalMove(1.0);
      break;
    case SDLK_DOWN:
      m_renderer.verticalMove(-1.0);
      break;
    case SDLK_LEFT:
      m_renderer.horizontalMove(-1.0);
      break;
    case SDLK_RIGHT:
      m_renderer.horizontalMove(1.0);
      break;
  }
}

void EventListener::visit(const sdl::MouseEvent & )
{
  LOG_DEBUG("MouseEvent arrived.");
}

void EventListener::visit(const sdl::QuitEvent &)
{
  LOG_DEBUG("QuitEvent arrived.");
  m_quit = true;
}

void EventListener::visit(const sdl::WindowEvent &)
{
  LOG_DEBUG("WindowEvent arrived.");
}

void EventListener::visit(const sdl::TimerEvent &)
{
}
