#ifndef MINE_SDL_EVENTVISITOR_HPP_INC
#define MINE_SDL_EVENTVISITOR_HPP_INC

namespace mine
{
  namespace sdl
  {
    class KeyEvent;
    class MouseEvent;
    class QuitEvent;
    class WindowEvent;

    class EventVisitor
    {
      public:
        virtual void visit(const KeyEvent &) = 0;
        virtual void visit(const MouseEvent &) = 0;
        virtual void visit(const QuitEvent &) = 0;
        virtual void visit(const WindowEvent &) = 0;
    };
  }
}


#endif
