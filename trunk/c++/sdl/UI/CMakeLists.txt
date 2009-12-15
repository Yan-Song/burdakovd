include_directories(${SDLApplication_SOURCE_DIR}/sdlapplication)

set(SRC Button Clickable Element ElementSet MouseOverable)

add_library(UI ${SRC})

target_link_libraries(UI sdlapplication)
