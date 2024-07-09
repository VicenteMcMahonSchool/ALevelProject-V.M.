#pragma once
#include "../../global/global.hpp"
#include "../general_game_object/general_game_object.hpp"

#define WIDTH_OF_TILE_MAP 64
#define HEIGHT_OF_TILE_MAP 64
#define NUMBER_OF_TILES WIDTH_OF_TILE_MAP *HEIGHT_OF_TILE_MAP
#define TILE_MAP_RECTANGLES_POSITION                                                     \
    this->rectangles[i].x = (i % WIDTH_OF_TILE_MAP) * this->tileSize - this->position.x; \
    this->rectangles[i].y = (i / WIDTH_OF_TILE_MAP) * this->tileSize - this->position.y;

enum TILE_TYPE
{
    TILE_AIR,
    TILE_PLATFORM
};

class TileMap : public GeneralGameObject
{
private:
    TILE_TYPE tileMap[NUMBER_OF_TILES];
    SDL_Rect rectangles[NUMBER_OF_TILES];
    unsigned int tileSize;

public:
    TileMap(Vector2 position, unsigned int tileSize);
    void update(double deltaTime);
    void draw(void);
    void setTile(size_t x, size_t y, TILE_TYPE tileType);
};