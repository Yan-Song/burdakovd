include_directories(${SDLApplication_SOURCE_DIR}/sdlapplication)

set(SRC Button Clickable ColorSelector Element ElementSet Label MouseOverable)

add_library(UI ${SRC})

set(LIBS ${LIBS} sdlapplication)

target_link_libraries(UI ${LIBS})
