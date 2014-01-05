#ifndef MINE_SDL_WINDOW_HPP_INC
#define MINE_SDL_WINDOW_HPP_INC

#include <SDL2/SDL.h>
#include <set>
#include <ostream>

#include <mine/goodies.hpp>
#include <mine/PixelPos.hpp>

namespace mine
{
  namespace sdl
  {
    enum class WindowFlag
    {
      FullScreen =        SDL_WINDOW_FULLSCREEN,         // fullscreen window
      FullScreenDesktop = SDL_WINDOW_FULLSCREEN_DESKTOP, // fullscreen window at the current desktop resolution
      OpenGL =            SDL_WINDOW_OPENGL,             // window usable with OpenGL context
      Shown =             SDL_WINDOW_SHOWN,              // window is visible
      Hidden =            SDL_WINDOW_HIDDEN,             // window is not visible
      Borderless =        SDL_WINDOW_BORDERLESS,         // no window decoration
      Resizable =         SDL_WINDOW_RESIZABLE,          // window can be resized
      Minimized =         SDL_WINDOW_MINIMIZED,          // window is minimized
      Maximized =         SDL_WINDOW_MAXIMIZED,          // window is maximized
      InputGrabbed =      SDL_WINDOW_INPUT_GRABBED,      // window has grabbed input focus
      InputFocus =        SDL_WINDOW_INPUT_FOCUS,        // window has input focus
      MouseFocus =        SDL_WINDOW_MOUSE_FOCUS,        // window has mouse focus
      Foreign =           SDL_WINDOW_FOREIGN,            // window not created by SDL
      HighDPI =           SDL_WINDOW_ALLOW_HIGHDPI,      // window should be created in high-DPI mode if supported (available since SDL 2.0.1)
    };

    std::ostream& operator<<(std::ostream& out, WindowFlag);

    class Window : NonTransferable
    {
      public:
        Window(const std::string & title,
               PixelPos startPos,
               PixelPos size,
               std::set<WindowFlag> flags);

        ~Window();
      private:
        friend std::ostream& operator<<(std::ostream&, const Window &);

        std::string m_title;
        PixelPos m_position; ///< position
        PixelPos m_size;

        SDL_Window * m_win;
    };
//    std::ostream& operator<<(std::ostream&, const Window &);
    inline std::ostream& operator<<(std::ostream& out, const Window & win)
    {
      return out << "title: " << win.m_title <<
                    ", pos: " << win.m_position <<
                    ", size: " << win.m_size;
    }
  }
}

#endif
