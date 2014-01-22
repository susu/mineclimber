#include <SDL2/SDL.h>
#include <iostream>

#include <mine/Logger.hpp>
#include <mine/Pos.hpp>
#include <mine/BlockContainer.hpp>
#include <mine/ClipRenderer.hpp>
#include <mine/Painter.hpp>
#include <mine/BlockType.hpp>
#include <mine/EventListener.hpp>

#include <mine/sdl/Context.hpp>
#include <mine/sdl/Window.hpp>
#include <mine/sdl/Renderer.hpp>
#include <mine/sdl/ImageContext.hpp>
#include <mine/sdl/Surface.hpp>
#include <mine/sdl/Texture.hpp>
#include <mine/sdl/EventWaitress.hpp>
#include <mine/sdl/EventVisitor.hpp>
#include <mine/sdl/events.hpp>

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

    Pos winStartPos = {100, 100};
    Pos winSize{640, 480};
    sdl::Window window("MineClimber",
                       winStartPos,
                       winSize,
                       {sdl::WindowFlag::Shown});
    sdl::Renderer renderer(window, {sdl::RendererFlag::Accelerated,
                                    sdl::RendererFlag::PresentVSync});

    // Create a background image from a PNG
    sdl::Texture background = sdl::Texture::CreateFromSurface(renderer,
        sdl::Surface::CreateFromPNG(ASSET_DIR + "/sky.png"));

    BlockContainer container;

    sdl::Texture block = sdl::Texture::CreateFromSurface(renderer,
        sdl::Surface::CreateFromPNG(ASSET_DIR + "/soil.png"));

    FRect startClip = {
      { -8.5,  6}, // lower-left corner
      { 16, 12} };  // width, height

    ClipRenderer clip(startClip, renderer);

    BlockContainer blocks;
    Painter painter(blocks, clip, std::move(block));

    LOG_DEBUG("Painter and BlockContainer are initialized.");

    // TODO Perlin-noise generated world
    for (int i = -20; i < 20; ++i)
    {
      blocks.createBlock(BlockType::Soil, i, 3);
      blocks.createBlock(BlockType::Soil, i, 4);
    }

    renderer.clear(); // clear the screen
    renderer.copyAll(background); // copy our background to renderer
    painter.drawBlocks();

    renderer.present(); // show the result to the user

    sdl::EventWaitress waitress;

    auto visitor = std::make_unique<EventListener>(clip);
    EventListener & vis = *visitor;
    waitress.addVisitor(std::move(visitor));

    while (!vis.shouldQuit())
    {
      // Re-draw
      renderer.clear(); // clear the screen
      renderer.copyAll(background); // copy our background to renderer
      painter.drawBlocks();
      renderer.present();

      waitress.waitFor(10); // wait with 10ms timeout
    }

    LOG_DEBUG("========================================================================");
  }
  catch (const MineException & ex)
  {
    std::cout << "!!! ---\n!!! ERROR: " << ex.what() << std::endl;
    std::cout << "!!! ---" << std::endl;
  }
  LOG_DEBUG("Bye.");
}
