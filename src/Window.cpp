#include <mine/sdl/Window.hpp>

#include <mine/goodies.hpp>
#include <mine/Logger.hpp>

using namespace mine::sdl;

Window::Window(const std::string & title,
               PixelPos startPos,
               PixelPos size,
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
                           startPos.m_width, startPos.m_height,
                           size.m_width, size.m_height, sumFlag);
}

Window::~Window()
{
  LOG_DEBUG("Closing window: title: ", m_title);
  SDL_DestroyWindow(m_win);
  m_win = nullptr;
}
