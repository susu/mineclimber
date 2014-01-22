#ifndef MINE_EVENTLISTENER_HPP_INC
#define MINE_EVENTLISTENER_HPP_INC

#include <mine/sdl/EventVisitor.hpp>

namespace mine
{
  class ClipRenderer;
  class EventListener : public sdl::EventVisitor
  {
    public:
      EventListener(ClipRenderer & renderer);

      bool shouldQuit() const
      { return m_quit; }

      void visit(const sdl::KeyEvent & ev) override;
      void visit(const sdl::MouseEvent & ) override;
      void visit(const sdl::QuitEvent &) override;
      void visit(const sdl::WindowEvent &) override;
      void visit(const sdl::TimerEvent &) override;

    private:
      bool m_quit = false;
      ClipRenderer & m_renderer;
  };
}

#endif
