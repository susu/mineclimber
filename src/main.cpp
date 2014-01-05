#include <SDL2/SDL.h>
#include <iostream>

#include <mine/Logger.hpp>
#include <mine/PixelPos.hpp>
#include <mine/sdl/Context.hpp>
#include <mine/sdl/Window.hpp>

using namespace mine;

int main()
{
  try
  {
    LOG_DEBUG("Main started.");
    sdl::Context context({sdl::SDLInitFlag::InitEverything});

    PixelPos winStartPos = {100, 100};
    PixelPos winSize{640, 480};
    sdl::Window window("MineClimber",
                       winStartPos,
                       winSize,
                       {sdl::WindowFlag::Shown});

    LOG_DEBUG("=====================================");
  }
  catch (const MineException & ex)
  {
    std::cout << "Error occured: " << ex.what() << std::endl;
  }
  LOG_DEBUG("Bye.");
}
