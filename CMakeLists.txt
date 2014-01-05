cmake_minimum_required(VERSION 2.8)

project(mineclimber)

if(APPLE OR UNIX)
  set(CMAKE_CXX_COMPILER "clang++")
endif()

FILE(GLOB SOURCE_FILES src/*.cpp)

add_executable(mineclimber ${SOURCE_FILES})

include_directories(include)

add_definitions(-std=c++11 -Wall -Werror -DMINE_DEBUG -g)

target_link_libraries(mineclimber SDL2 SDL2_image)

