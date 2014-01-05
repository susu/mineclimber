#ifndef MINE_SDL_IMAGECONTEXT_HPP_INC
#define MINE_SDL_IMAGECONTEXT_HPP_INC

#include <SDL2/SDL_image.h>
#include <set>
#include <ostream>
#include <mine/goodies.hpp>

namespace mine
{
  namespace sdl
  {
    enum class IMGInitFlag
    {
      JPG = IMG_INIT_JPG,
      PNG = IMG_INIT_PNG,
      TIF = IMG_INIT_TIF,
    };

    inline std::ostream& operator<<(std::ostream& out, IMGInitFlag flag)
    {
      switch (flag)
      {
        case IMGInitFlag::JPG: return out << "JPG";
        case IMGInitFlag::PNG: return out << "PNG";
        case IMGInitFlag::TIF: return out << "TIF";
      }
      return out << "-unknown-";
    }

    class ImageContext : NonTransferable
    {
      public:
        ImageContext(std::set<IMGInitFlag> flags);
        ~ImageContext();
    };
  }
}

#endif
