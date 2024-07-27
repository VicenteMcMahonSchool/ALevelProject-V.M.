#pragma once
#include "../../global/global.hpp"
#include "../general_game_object/general_game_object.hpp"

#define WIDTH_OF_TILE_MAP 256
#define HEIGHT_OF_TILE_MAP 128
#define NUMBER_OF_TILES WIDTH_OF_TILE_MAP *HEIGHT_OF_TILE_MAP
#define TILE_MAP_RECTANGLES_POSITION                                                     \
    this->rectangles[i].x = (i % WIDTH_OF_TILE_MAP) * this->tileSize - this->position.x; \
    this->rectangles[i].y = (i / WIDTH_OF_TILE_MAP) * this->tileSize - this->position.y;

enum __attribute__((__packed__)) TILE_TYPE
{
    TILE_NONE = 0,
    TILE_AIR,
    TILE_PLATFORM,
    TILE_BOARDER,
};

struct TilesAroundPosition
{
    TILE_TYPE *centre = NULL;
    TILE_TYPE *left = NULL;
    TILE_TYPE *right = NULL;
    TILE_TYPE *top = NULL;
    TILE_TYPE *bottom = NULL;
    TILE_TYPE *topLeft = NULL;
    TILE_TYPE *topRight = NULL;
    TILE_TYPE *bottomLeft = NULL;
    TILE_TYPE *bottomRight = NULL;
};

struct TileCentres
{
    Vector2 left;
    Vector2 centre;
    Vector2 right;
    Vector2 topLeft;
    Vector2 top;
    Vector2 topRight;
    Vector2 bottomLeft;
    Vector2 bottom;
    Vector2 bottomRight;
};

class TileMap : public GeneralGameObject
{
private:
    TILE_TYPE tileMap[NUMBER_OF_TILES];
    SDL_Rect rectangles[NUMBER_OF_TILES];
    // unsigned int tileSize;
    GETTER_AND_SETTER_HPP(unsigned int, tileSize, TileSize);

public:
    TileMap(Vector2 position, unsigned int tileSize);
    void update(double deltaTime);
    void draw(void);
    void setTile(size_t x, size_t y, TILE_TYPE tileType);
    size_t getIndexFromPosition(Vector2 position);
    TILE_TYPE *getTileAtPosition(Vector2 position);
    TilesAroundPosition getTilesAroundPosition(Vector2 position);
    void setTilesAroundPosition(Vector2 position, TILE_TYPE tile);
    Vector2 getCentrePositionOfTile(TILE_TYPE *tile);
    TileCentres getTileCentresAroundPositionOfTile(TILE_TYPE *tile);
};