#include <mine/sdl/Window.hpp>

#include <mine/goodies.hpp>
#include <mine/Logger.hpp>

using namespace mine::sdl;

Window::Window(const std::string & title,
               Pos startPos,
               Pos size,
               std::set<WindowFlag> flags)
  : m_title(title)
  , m_position(startPos)
  , m_size(size)
  , m_win(nullptr)
{
  std::underlying_type<WindowFlag>::type sumFlag = 0;
  for (auto f : flags)
  {
    sumFlag |= to_underlying_cast(f);
  }

  LOG_DEBUG("Creating window: ", *this);
  m_win = SDL_CreateWindow(title.c_str(),
                           startPos.x, startPos.y,
                           size.x, size.y, sumFlag);
}

Window::~Window()
{
  LOG_DEBUG("Closing window: title: ", m_title);
  SDL_DestroyWindow(m_win);
  m_win = nullptr;
}
