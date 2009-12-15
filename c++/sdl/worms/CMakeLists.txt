include_directories(${SDLApplication_SOURCE_DIR}/sdlapplication ${SDLApplication_SOURCE_DIR})

set(SRC BattleField Config Engine main MainMenu MenuItem Manual Registrator SettingsDialog Worm WormsApplication)

add_executable(Worms ${SRC})

target_link_libraries(Worms SDL SDLmain SDL_ttf sdlapplication UI)
