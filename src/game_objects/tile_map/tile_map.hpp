#pragma once
#include "../../global/global.hpp"

enum TILE_TYPE
{
    TILE_AIR,
    TILE_PLATFORM
};

class TileMap
{
private:
    TILE_TYPE *tileMap;

public:
    TileMap(void);
    ~TileMap();
};