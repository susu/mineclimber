#include <SDL2/SDL.h>
#include <iostream>

#include <mine/Logger.hpp>
#include <mine/Pos.hpp>
#include <mine/BlockContainer.hpp>
#include <mine/ClipRenderer.hpp>
#include <mine/Painter.hpp>
#include <mine/BlockType.hpp>

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

class MyVisitor : public sdl::EventVisitor
{
  public:
    bool shouldQuit() const
    { return m_quit; }

    void visit(const sdl::KeyEvent & ev) override
    {
      LOG_DEBUG("KeyEvent arrived: ", ev);
    }

    void visit(const sdl::MouseEvent & ) override
    {
      LOG_DEBUG("MouseEvent arrived.");
    }

    void visit(const sdl::QuitEvent &) override
    {
      LOG_DEBUG("QuitEvent arrived.");
      m_quit = true;
    }
  private:
    bool m_quit = false;
};

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

    Rect startClip = {
      { -8,  6},   // upper-left corner
      { 16, 12} }; // width, height

    ClipRenderer clip(startClip, renderer);

    BlockContainer blocks;
    Painter painter(blocks, clip);

    LOG_DEBUG("Painter and BlockContainer are initialized.");

    blocks.createBlock(BlockType::Soil, 0, 0);

    // TODO painter as BlockVisistor...

    renderer.clear(); // clear the screen
    renderer.copyAll(background); // copy our background to renderer
    renderer.present(); // show the result to the user

    sdl::EventWaitress waitress;

    auto visitor = std::make_unique<MyVisitor>();
    MyVisitor & vis = *visitor;
    waitress.addVisitor(std::move(visitor));

    while (!vis.shouldQuit())
    {
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
