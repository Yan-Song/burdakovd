include_directories(${SDLApplication_SOURCE_DIR}/sdlapplication)

set(SRC BattleField Config main Manual Registrator Worm WormsApplication)

add_executable(Worms ${SRC})

target_link_libraries(Worms sdlapplication)
