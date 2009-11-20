cmake_minimum_required(VERSION 2.6)

project(SDLApplication CXX)

include_directories(/usr/include/SDL)
add_definitions(-DTR1_PREFIX -W -Wall -Wextra -pedantic -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor -Wold-style-cast -Wconversion -Wsign-conversion -Winit-self -Werror)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -funit-at-a-time -funswitch-loops -Wdisabled-optimization")

add_subdirectory(sdlapplication)
add_subdirectory(primitives)
add_subdirectory(RayTracing)
add_subdirectory(RayTracingDemo)
