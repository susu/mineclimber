#ifndef MINE_SDL_EVENTS_HPP_INC
#define MINE_SDL_EVENTS_HPP_INC

#include <SDL2/SDL_events.h>
#include <ostream>
#include <mine/sdl/EventVisitor.hpp>

namespace mine
{
  namespace sdl
  {
    class EventBase
    {
      public:
        virtual ~EventBase() = default;
        virtual void accept(EventVisitor & visitor) const = 0;
        virtual void toStream(std::ostream & out) const = 0;
    };

    inline std::ostream& operator<<(std::ostream & out, const EventBase & event)
    {
      event.toStream(out);
      return out;
    }

    template<typename T>
    class Event : public EventBase
    {
      void accept(EventVisitor & visitor) const override
      { visitor.visit(dynamic_cast<const T&>(*this)); }
    };

    class QuitEvent : public Event<QuitEvent>
    {
      public:
        QuitEvent(SDL_QuitEvent ev);
        void toStream(std::ostream & out) const override
        {}
    };

    class MouseEvent : public Event<MouseEvent>
    {
      public:
        MouseEvent(SDL_MouseMotionEvent motion);
        void toStream(std::ostream & out) const override
        {}
    };

    class TimerEvent : public Event<TimerEvent>
    {
      public:
        TimerEvent();

        void toStream(std::ostream & out) const override
        {}
    };
  }
}

#include <mine/sdl/KeyEvent.hpp>

#endif
