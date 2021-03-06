#include <mine/sdl/Renderer.hpp>

#include <mine/Logger.hpp>
#include <mine/Exceptions.hpp>
#include <mine/Enforce.hpp>

#include <mine/sdl/Window.hpp>
#include <mine/sdl/Texture.hpp>

using namespace mine::sdl;

std::ostream & mine::sdl::operator<<(std::ostream& out, RendererFlag flag)
{
  switch (flag)
  {
    case RendererFlag::Software:      return out << "Software";
    case RendererFlag::Accelerated:   return out << "Accelerated";
    case RendererFlag::PresentVSync:  return out << "PresentVSync";
    case RendererFlag::TargetTexture: return out << "TargetTexture";
  }
  return out << "-unknown-";
}

Renderer::Renderer(const Window & window, std::set<RendererFlag> renderFlags)
  : m_renderer(nullptr)
{
  LOG_DEBUG("Initializing renderer for window: (", window,
            "), renderer-flags: ", flagsetToString(renderFlags));
  auto flagValue = flagsetToValue(renderFlags);

  m_renderer = SDL_CreateRenderer(window.getHandle(),
                                  -1 /* auto-select device */,
                                  flagValue);
  m_winSize = window.getSize();
  if (m_renderer == nullptr)
  {
    MINE_RAISE(SDLException, "Cannot initialize renderer: " << SDL_GetError());
  }
}

Renderer::~Renderer()
{
  if (m_renderer != nullptr)
    SDL_DestroyRenderer(m_renderer);
  m_renderer = nullptr;
}

void Renderer::clear()
{
  ENFORCE(m_renderer != nullptr, "Renderer object is invalid!");
  SDL_RenderClear(m_renderer);
}

void Renderer::copyAll(const Texture & texture)
{
  ENFORCE(m_renderer != nullptr, "Renderer object is invalid!");
  SDL_RenderCopy(m_renderer, texture.getHandle(), NULL, NULL);
}

void Renderer::copyTo(const Texture & texture, const Rect & dest)
{
  ENFORCE(m_renderer != nullptr, "Renderer object is invalid!");
  SDL_Rect sdlDest;
  sdlDest.x = dest.m_pos.x;
  sdlDest.y = dest.m_pos.y;
  sdlDest.w = dest.m_dimension.x;
  sdlDest.h = dest.m_dimension.y;
  SDL_RenderCopy(m_renderer, texture.getHandle(), NULL, &sdlDest);
}

void Renderer::copyFrom(const Texture & texture, const Rect & src)
{
  ENFORCE(m_renderer != nullptr, "Renderer object is invalid!");
  SDL_Rect sdlSource;
  sdlSource.x = src.m_pos.x;
  sdlSource.y = src.m_pos.y;
  sdlSource.w = src.m_dimension.x;
  sdlSource.h = src.m_dimension.y;
  SDL_RenderCopy(m_renderer, texture.getHandle(), &sdlSource, NULL);
}

void Renderer::present()
{
  ENFORCE(m_renderer != nullptr, "Renderer object is invalid!");
  SDL_RenderPresent(m_renderer);
}
