#include "./tile_map.hpp"

TileMap::TileMap(Vector2 position) : GeneralGameObject(position)
{
    this->tileMap = (TILE_TYPE *)calloc(windowWidth * windowHeight, sizeof(TILE_TYPE));
}
TileMap::~TileMap()
{
    free(this->tileMap);
}