set(SRC Affine Circle2D CompoundObject Cube DemoScene Font Frustum Geometry2D Pencil Polygon Scene SDLApplication SDLException Segment Sprite Tetragon Timer Triangle3D Vector)

add_library (sdlapplication ${SRC})

target_link_libraries(sdlapplication SDL SDLmain SDL_ttf pthread)

