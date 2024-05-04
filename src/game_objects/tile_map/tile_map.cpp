#include "./tile_map.hpp"

TileMap::TileMap(void)
{
    this->tileMap = (TILE_TYPE *)calloc(windowWidth * windowHeight, sizeof(TILE_TYPE));
}
TileMap::~TileMap()
{
    free(this->tileMap);
}