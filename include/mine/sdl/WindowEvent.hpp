#ifndef MINE_SDL_WINDOWEVENT_HPP_INC
#define MINE_SDL_WINDOWEVENT_HPP_INC

#include <SDL2/SDL_events.h>
#include <mine/sdl/events.hpp>

namespace mine
{
  namespace sdl
  {
    class WindowEvent : public Event<WindowEvent>
    {
      public:
        WindowEvent(SDL_WindowEvent win);

        void toStream(std::ostream & out) const override
        {}
    };
  }
}

#endif
