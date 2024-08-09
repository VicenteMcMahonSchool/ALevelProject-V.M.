#pragma once
#include <stdexcept>
#include <dlfcn.h>
#include "../../global/global.hpp"
#include "../general_game_object/general_game_object.hpp"
#include "../../game_objects_class/game_objects_class.hpp"

#define TILE_MAP_CONSTRUCTOR_ARGUMENTS Vector2 position, unsigned int tileSize
#define TILE_MAP_CONSTRUCTOR_ARGUMENTS_NAMES position, tileSize
#define WIDTH_OF_TILE_MAP 128
#define HEIGHT_OF_TILE_MAP 64
#define NUMBER_OF_TILES WIDTH_OF_TILE_MAP *HEIGHT_OF_TILE_MAP
#define TILE_MAP_RECTANGLES_POSITION                                                     \
    this->rectangles[i].x = (i % WIDTH_OF_TILE_MAP) * this->tileSize - this->position.x; \
    this->rectangles[i].y = (i / WIDTH_OF_TILE_MAP) * this->tileSize - this->position.y;

enum __attribute__((__packed__)) TILE_TYPE
{
    TILE_NONE = 0X00,
    TILE_AIR = 0X01,
    TILE_BOARDER = 0X02,
    TILE_PLATFORM = 0X03,
    TILE_WIN = 0X04,
    TILE_LOSE = 0X05,
    TILE_ROTATION = 0X06,
    TILE_ENEMY_SPAWNER = 0X07,
    TILE_SPAWN = 0X08,
    TILE_MAXIMUM_VALUE,
};

struct TilesAroundTile
{
    const TILE_TYPE *centre = NULL;
    const TILE_TYPE *left = NULL;
    const TILE_TYPE *right = NULL;
    const TILE_TYPE *top = NULL;
    const TILE_TYPE *bottom = NULL;
    const TILE_TYPE *topLeft = NULL;
    const TILE_TYPE *topRight = NULL;
    const TILE_TYPE *bottomLeft = NULL;
    const TILE_TYPE *bottomRight = NULL;
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

struct __attribute__((__packed__)) TileAttributes
{
    bool isCollidable;
};

TileAttributes getTileAttributes(const TILE_TYPE tile);
TileAttributes getTileAttributes(const TILE_TYPE *tilePointer);

class TileMap : public GeneralGameObject
{
private:
    TILE_TYPE tileMap[NUMBER_OF_TILES];
    SDL_Rect rectangles[NUMBER_OF_TILES];
    GETTER_AND_SETTER_HPP(unsigned int, tileSize, TileSize)

public:
    TileMap(TILE_MAP_CONSTRUCTOR_ARGUMENTS);
    bool tileOutlines = false;
    void tick(void);
    void update(double deltaTime);
    void draw(void);
    void drawShadows(void);
    void saveMap(void);
    void setTileAtPosition(Vector2 position, TILE_TYPE tileType);
    const TILE_TYPE *getSpawnTile(void);
    size_t getIndexFromPosition(Vector2 position);
    const TILE_TYPE *getTileAtPosition(Vector2 position);
    TilesAroundTile getTilesAroundIndex(size_t index);
    TilesAroundTile getTilesAroundPosition(Vector2 position);
    Vector2 getCentrePositionOfTile(const TILE_TYPE *tile);
    TileCentres getTileCentresAroundPositionOfTile(const TILE_TYPE *tile);
};