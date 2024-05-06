#pragma once
#include "../../global/global.hpp"
#include "../general_game_object/general_game_object.hpp"

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