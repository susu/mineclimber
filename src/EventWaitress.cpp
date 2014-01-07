#include <mine/sdl/EventWaitress.hpp>

#include <SDL2/SDL_events.h>
#include <mine/Exceptions.hpp>
#include <mine/Logger.hpp>
#include <mine/sdl/EventVisitor.hpp>
#include <mine/sdl/events.hpp>

using namespace mine::sdl;

void EventWaitress::addVisitor(std::unique_ptr<EventVisitor> && visitor)
{
  visitor->visit(KeyEvent(SDL_KeyboardEvent()));
  m_visitors.push_back(std::move(visitor));
}

void EventWaitress::waitFor(uint32_t timeout)
{
  ::SDL_Event ev;
  int result = SDL_WaitEventTimeout(&ev, timeout);
  if (result == 0)
  {
    if (strlen(SDL_GetError()) > 0)
      MINE_RAISE(SDLException, "Error while waiting for an event! " << SDL_GetError());

    return;
  }

  std::unique_ptr<EventBase> event = CreateEvent(ev);
  if (!event)
  {
    LOG_DEBUG("Unknown event arrived: type=", ev.type);
    return;
  }

  for (const auto & visitor : m_visitors)
  {
    event->accept(*visitor);
  }
}

std::unique_ptr<EventBase> EventWaitress::CreateEvent(const SDL_Event & ev)
{
  switch (ev.type)
  {
    case SDL_QUIT:
      return std::make_unique<QuitEvent>(ev.quit);

    case SDL_KEYDOWN:
    case SDL_KEYUP:
      return std::make_unique<KeyEvent>(ev.key);

    case SDL_MOUSEMOTION:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEWHEEL:
      return std::make_unique<MouseEvent>(ev.motion);
  }
  return nullptr;
}
