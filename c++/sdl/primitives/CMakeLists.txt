include_directories(${SDLApplication_SOURCE_DIR}/sdlapplication)

set(SRC primitives main)

add_executable(primitives ${SRC})

set(LIBS ${LIBS} sdlapplication)

target_link_libraries(primitives ${LIBS})
