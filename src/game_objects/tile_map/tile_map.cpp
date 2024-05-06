#include "./tile_map.hpp"

TileMap::TileMap(Vector2 position, unsigned int tileSize) : GeneralGameObject(position), tileSize(tileSize)
{
    this->numberOfTiles = (unsigned int)(windowWidth * (double)windowHeight / (tileSize * tileSize));
    this->tileMap = (TILE_TYPE *)calloc(this->numberOfTiles, sizeof(TILE_TYPE));
}
TileMap::~TileMap()
{
    free(this->tileMap);
}
void TileMap::update(double deltaTime) {}
void TileMap::draw(void) {}