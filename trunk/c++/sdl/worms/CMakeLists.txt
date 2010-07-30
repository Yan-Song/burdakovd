include_directories(${SDLApplication_SOURCE_DIR}/sdlapplication ${SDLApplication_SOURCE_DIR})

set(SRC BattleField Battle Config Counter Engine main MainMenu MenuItem Manual Registrator SettingsDialog SimplePoint Worm WormsApplication CountingWorm)

add_executable(Worms ${SRC})

set(LIBS ${LIBS} sdlapplication UI)

target_link_libraries(Worms ${LIBS})
