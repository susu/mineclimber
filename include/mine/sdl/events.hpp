#ifndef MINE_SDL_EVENTS_HPP_INC
#define MINE_SDL_EVENTS_HPP_INC

#include <mine/sdl/EventVisitor.hpp>
#include <SDL2/SDL_events.h>

namespace mine
{
  namespace sdl
  {
    class EventBase
    {
      public:
        virtual ~EventBase() = default;
        virtual void accept(EventVisitor & visitor) const = 0;
    };

    template<typename T>
    class Event : public EventBase
    {
      void accept(EventVisitor & visitor) const override
      { visitor.visit(dynamic_cast<const T&>(*this)); }
    };

    class KeyEvent : public Event<KeyEvent>
    {
      public:
        KeyEvent(SDL_KeyboardEvent ev);
    };

    class QuitEvent : public Event<QuitEvent>
    {
      public:
        QuitEvent(SDL_QuitEvent ev);
    };

    class MouseEvent : public Event<MouseEvent>
    {
      public:
        MouseEvent(SDL_MouseMotionEvent motion);
    };
  }
}

#endif
