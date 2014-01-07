#ifndef MINE_SDL_EVENTWAITRESS_HPP_INC
#define MINE_SDL_EVENTWAITRESS_HPP_INC

#include <memory>
#include <vector>

union SDL_Event;

namespace mine
{
  namespace sdl
  {
    class EventVisitor;
    class EventBase;

    class EventWaitress
    {
      public:
        void addVisitor(std::unique_ptr<EventVisitor> && visitor);
        void waitFor(uint32_t timeout);

      private:
        std::unique_ptr<EventBase> CreateEvent(const SDL_Event & ev);
        std::vector< std::unique_ptr<EventVisitor> > m_visitors;
    };

  }
}

#endif
