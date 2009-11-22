include_directories(${SDLApplication_SOURCE_DIR})

set(SRC Camera CompoundObject Frustum Material NormalizedVector3D Plane Ray Scene SierpinskiPyramide Sphere Tetragon Texture Triangle)

add_library(RayTracing ${SRC})

target_link_libraries(RayTracing sdlapplication)
