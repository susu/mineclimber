#include <mine/sdl/Texture.hpp>
#include <mine/Logger.hpp>
#include <mine/sdl/Surface.hpp>
#include <mine/sdl/Renderer.hpp>

using namespace mine::sdl;

Texture::Texture(SDL_Texture * texture)
  : m_texture(texture)
{}

Texture::Texture(Texture&& other)
{
  m_texture = other.m_texture;
  other.m_texture = nullptr;
}

Texture& Texture::operator=(Texture&& other)
{
  m_texture = other.m_texture;
  other.m_texture = nullptr;
  return *this;
}

Texture::~Texture()
{
  if (m_texture != nullptr)
  {
    LOG_DEBUG("Destroying texture: ", m_texture);
    SDL_DestroyTexture(m_texture);
    m_texture = nullptr;
  }
}

Texture Texture::CreateFromSurface(const Renderer & renderer, const Surface & surface)
{
  LOG_DEBUG("Creating texture from surface: ", surface.getHandle());

  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer.getHandle(),
                                                       surface.getHandle());
  return std::move(Texture(texture));
}
