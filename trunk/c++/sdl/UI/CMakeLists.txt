include_directories(${SDLApplication_SOURCE_DIR}/sdlapplication)

set(SRC Clickable Element MouseOverable)

add_library(UI ${SRC})

target_link_libraries(UI sdlapplication)
