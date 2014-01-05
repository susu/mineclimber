#include <mine/sdl/Context.hpp>

#include <mine/goodies.hpp>
#include <mine/Logger.hpp>

using namespace mine::sdl;

Context::Context(std::set<SDLInitFlag> flags)
{
  std::underlying_type<SDLInitFlag>::type sumFlags = 0;

  std::ostringstream flagNames;
  for (auto flag : flags)
  {
    sumFlags |= to_underlying_cast(flag);
    flagNames << flag;
  }

  LOG_DEBUG("Initializing SDL with flags: ", flagNames.str());
  if (SDL_Init(sumFlags) == -1)
    MINE_RAISE(MineException, "Cannot initialize SDL! Error: " << SDL_GetError());
}

Context::~Context()
{
  LOG_DEBUG("Cleaning up SDL context");
  SDL_Quit();
}
