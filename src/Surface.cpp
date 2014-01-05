#include <mine/sdl/Surface.hpp>

#include <SDL2/SDL_image.h>
#include <mine/Exceptions.hpp>
#include <mine/Logger.hpp>

using namespace mine::sdl;

Surface Surface::CreateFromPNG(const std::string path)
{
  LOG_DEBUG("Creating surface from PNG file: ", path);

  std::string extension = path.substr(path.find_last_of('.')+1);

  if (ToUpper(extension) != "PNG")
    MINE_RAISE(SDLException, "It is not a png file: " << path);

  SDL_Surface * image = IMG_Load(path.c_str());
  if (image == nullptr)
    MINE_RAISE(SDLException, "Couldn't load image: " << IMG_GetError());

  return std::move(Surface(image));
}

Surface::Surface(SDL_Surface * surface)
  : m_surface(surface)
{}

Surface::Surface(Surface&& other)
{
  m_surface = other.m_surface;
  other.m_surface = nullptr;
}

Surface& Surface::operator=(Surface&& other)
{
  m_surface = other.m_surface;
  other.m_surface = nullptr;
  return *this;
}

Surface::~Surface()
{
  if (m_surface != nullptr)
  {
    LOG_DEBUG("Freeing surface: ", m_surface);
    SDL_FreeSurface(m_surface);
    m_surface = nullptr;
  }
}
