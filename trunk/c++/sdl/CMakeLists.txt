cmake_minimum_required(VERSION 2.6)

project(SDLApplication CXX)

include_directories(/usr/include/SDL)
add_definitions(-DTR1_PREFIX)

add_subdirectory(sdlapplication)
add_subdirectory(primitives)
add_subdirectory(RayTracing)
add_subdirectory(RayTracingDemo)
