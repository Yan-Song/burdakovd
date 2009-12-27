include_directories(${SDLApplication_SOURCE_DIR} ${SDLApplication_SOURCE_DIR}/RayTracing)

set(SRC Demo main)

add_executable(RayTracingDemo ${SRC})

set(LIBS ${LIBS} sdlapplication RayTracing)

target_link_libraries(RayTracingDemo ${LIBS})
