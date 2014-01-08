#ifndef MINE_SDL_KEYEVENT_HPP_INC
#define MINE_SDL_KEYEVENT_HPP_INC

#include <SDL2/SDL_events.h>
#include <mine/sdl/events.hpp>

namespace mine
{
  namespace sdl
  {
    enum class KeyState : decltype(SDL_PRESSED)
    {
      Pressed  = SDL_PRESSED,
      Released = SDL_RELEASED
    };
    std::ostream& operator<<(std::ostream & out, KeyState state);

    enum class KeyRepeat
    {
      Real,
      Repeat,
    };
    std::ostream& operator<<(std::ostream & out, KeyRepeat repeat);

    class KeyEvent : public Event<KeyEvent>
    {
      public:
        typedef int Keycode;
        KeyEvent(SDL_KeyboardEvent ev);
        void toStream(std::ostream & out) const override;

        uint32_t GetWindowsId() const
        { return m_winId; }

        /**
         *  Returns whether the actual key is Pressed or Released.
         */
        KeyState GetKeyState() const
        { return m_state; }

        /**
         *  Returns whether the actual key is a repeat event or a "real" one.
         */
        KeyRepeat GetRepeat() const
        { return m_repeat; }

        /**
         * Returns the scancode of the event (e.g. SDL_SCANCODE_PRINTSCREEN),
         * which is layout-independent.
         */
        SDL_Scancode GetScancode() const
        { return m_scancode; }

        /**
         * Returns the (virtual) keycode of the event (e.g. SDLK_1, or 'a'), which is
         * layout-dependent.
         */
        Keycode GetKeycode() const
        { return m_keycode; }

        /**
         * Returns the active modifier (e.g. KMOD_LCTRL). If there is multiple pressed
         * modifier, than they will be OR'd together.
         */
        uint16_t GetModifier() const
        { return m_modifier; }

      private:
        uint32_t   m_winId;
        KeyState   m_state;
        KeyRepeat  m_repeat;

        // These event attributes aren't wrapped to enum classes, simply because I'm lazy.
        SDL_Scancode           m_scancode;
        Keycode                m_keycode;
        uint16_t               m_modifier;
    };
  }
}

#endif
