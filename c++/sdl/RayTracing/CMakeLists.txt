include_directories(${SDLApplication_SOURCE_DIR})

set(SRC Camera CompoundObject Frustum Material NormalizedVector3D Plane Scene SierpinskiPyramide Sphere Tetragon Texture Triangle)

add_library(RayTracing ${SRC})

set(LIBS ${LIBS} sdlapplication)

target_link_libraries(RayTracing ${LIBS})
