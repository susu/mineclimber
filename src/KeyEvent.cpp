#include <mine/sdl/KeyEvent.hpp>
#include <mine/goodies.hpp>

using namespace mine::sdl;

std::ostream& mine::sdl::operator<<(std::ostream & out, KeyState state)
{
  switch (state)
  {
    case KeyState::Pressed:  return out << "pressed";
    case KeyState::Released: return out << "released";
  }
  return out << "-unknown-";
};

std::ostream& mine::sdl::operator<<(std::ostream & out, KeyRepeat repeat)
{
  switch (repeat)
  {
    case KeyRepeat::Real:   return out << "real";
    case KeyRepeat::Repeat: return out << "repeat";
  }
  return out << "-unknown-";
};

KeyEvent::KeyEvent(SDL_KeyboardEvent ev)
  : m_winId(ev.windowID)
  , m_state(from_underlying_cast<KeyState>(ev.state))
  , m_repeat( (ev.repeat != 0 ? KeyRepeat::Repeat : KeyRepeat::Real ) )
  , m_scancode(ev.keysym.scancode)
  , m_keycode(ev.keysym.sym)
  , m_modifier(ev.keysym.mod)
{
}

void KeyEvent::toStream(std::ostream & out) const
{
  out << "KeyEvent: " <<
         "scancode-value: " << m_scancode <<
         ", keycode-value: " << m_keycode <<
         ", active-modifier-value: " << m_modifier <<
         ", window-ID: " << m_winId <<
         ", state: " << m_state <<
         ", repeat: " << m_repeat;
}

