#pragma once
#include "../../global/global.hpp"
#include "../general_game_object/general_game_object.hpp"

#define TILE_MAP_RECTANGLES_POSITION                                                                  \
    this->rectangles[i].x = (i % (windowWidth / this->tileSize)) * this->tileSize - this->position.x; \
    this->rectangles[i].y = (i * this->tileSize) / windowWidth * this->tileSize - this->position.y;

enum TILE_TYPE
{
    TILE_AIR,
    TILE_PLATFORM
};

class TileMap : public GeneralGameObject
{
private:
    TILE_TYPE *tileMap;
    SDL_Rect *rectangles;
    unsigned int tileSize;
    unsigned int numberOfTiles;

public:
    TileMap(Vector2 position, unsigned int tileSize);
    ~TileMap();
    void update(double deltaTime);
    void draw(void);
};