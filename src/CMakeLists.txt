
# TODO separate lib for mine::sdl
set(SOURCE_FILES
  BlockContainer.cpp
  Block.cpp
  Chunk.cpp
  ChunkStorage.cpp
  ClipRenderer.cpp
  CMakeLists.txt
  Context.cpp
  EventListener.cpp
  events.cpp
  EventWaitress.cpp
  ImageContext.cpp
  KeyEvent.cpp
  Logger.cpp
  Painter.cpp
  Renderer.cpp
  SoilBlock.cpp
  Surface.cpp
  Texture.cpp
  Window.cpp
  WindowEvent.cpp
  )


add_library(mine SHARED ${SOURCE_FILES})
add_executable(mineclimber main.cpp)

find_library(SDL2 SDL2_image)
target_link_libraries(mineclimber mine SDL2 SDL2_image)


