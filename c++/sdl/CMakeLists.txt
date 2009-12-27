cmake_minimum_required(VERSION 2.6)

project(SDLApplication CXX)

include_directories(/usr/include/SDL)
add_definitions(-DTR1_PREFIX -W -Wall -Wextra -pedantic -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Wconversion -Wsign-conversion -Winit-self -Werror)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funit-at-a-time -funswitch-loops -Wdisabled-optimization")
set(CMAKE_CXX_FLAGS_PROFILE "${CMAKE_CXX_FLAGS_PROFILE} -g -pg -O0")

set(LIBS ${LIBS} pthread SDL SDLmain SDL_ttf SDL_image)

add_subdirectory(sdlapplication)
add_subdirectory(primitives)
add_subdirectory(RayTracing)
add_subdirectory(RayTracingDemo)
add_subdirectory(UI)
add_subdirectory(worms)

