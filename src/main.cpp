#include <SDL2/SDL.h>
#include <iostream>

#include <mine/Logger.hpp>
#include <mine/PixelPos.hpp>
#include <mine/sdl/Context.hpp>
#include <mine/sdl/Window.hpp>
#include <mine/sdl/Renderer.hpp>
#include <mine/sdl/ImageContext.hpp>
#include <mine/sdl/Surface.hpp>
#include <mine/sdl/Texture.hpp>

using namespace mine;

const std::string ASSET_DIR = "../assets";

int main()
{
  try
  {
    LOG_DEBUG("Main started.");
    // initializing the whole SDL context
    sdl::Context context({sdl::SDLInitFlag::InitEverything});

    // Initializing SDL_image only for PNG (separated library)
    sdl::ImageContext imgContext({sdl::IMGInitFlag::PNG});

    PixelPos winStartPos = {100, 100};
    PixelPos winSize{640, 480};
    sdl::Window window("MineClimber",
                       winStartPos,
                       winSize,
                       {sdl::WindowFlag::Shown});
    sdl::Renderer renderer(window, {sdl::RendererFlag::Accelerated,
                                    sdl::RendererFlag::PresentVSync});

    // Create a background image from a PNG
    sdl::Texture background = sdl::Texture::CreateFromSurface(renderer,
        sdl::Surface::CreateFromPNG(ASSET_DIR + "/sky.png"));
    std::cout << &background;

    renderer.clear(); // clear the screen
    renderer.copy(background); // copy our background to renderer
    renderer.present(); // show the result to the user

    LOG_DEBUG("========================================================================");
    LOG_DEBUG("3"); SDL_Delay(1000);
    LOG_DEBUG("2"); SDL_Delay(1000);
    LOG_DEBUG("1"); SDL_Delay(1000);
  }
  catch (const MineException & ex)
  {
    std::cout << "!!! --- !!! ERROR: " << ex.what() << std::endl;
  }
  LOG_DEBUG("Bye.");
}
