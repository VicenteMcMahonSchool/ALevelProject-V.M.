#include "./tile_map.hpp"

TileMap::TileMap(Vector2 position, unsigned int tileSize) : GeneralGameObject(position), tileSize(tileSize)
{
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
        rectangles[i].w = tileSize;
        rectangles[i].h = tileSize;
    }
}
void TileMap::update(double deltaTime)
{
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
    }
}
void TileMap::draw(void)
{
    // SDL_SetRenderDrawColour(renderer, colour.r, colour.g, colour.b, colour.a); // Sets draw colour.
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        rectangles[i].x -= cameraPosition.x - windowWidth / 2;
        rectangles[i].y -= cameraPosition.y - windowHeight / 2;
        if (tileMap[i] == TILE_AIR)
            SDL_SetRenderDrawColour(renderer, 0XDD, 0X00, 0X00, 0X00);
        else if (tileMap[i] == TILE_PLATFORM)
        {
            // SDL_SetRenderDrawColour(renderer, 0X33, 0XDD, 0X33, 0XFF);
            SDL_SetRenderDrawColour(renderer, 0X77, 0X33, 0X33, 0XFF);
            SDL_RenderFillRect(renderer, rectangles + i); // Fill rectangle.
        }
        SDL_RenderDrawRect(renderer, rectangles + i);
    }
    GeneralGameObject::draw();
}

void TileMap::setTile(size_t x, size_t y, TILE_TYPE tileType)
{
    tileMap[y * WIDTH_OF_TILE_MAP + x % WIDTH_OF_TILE_MAP] = tileType;
}

size_t TileMap::getIndexFromPosition(Vector2 position)
{
    return (size_t)(position.y) / tileSize * WIDTH_OF_TILE_MAP + (size_t)(position.x) / tileSize;
}

TILE_TYPE *TileMap::getTileAtPosition(Vector2 position)
{
    size_t index = getIndexFromPosition(position);
    if (index > NUMBER_OF_TILES || index < 0)
        return NULL;
    return tileMap + index;
}

void TileMap::getTilesAroundPosition(Vector2 position, TILE_TYPE *tiles[9])
{
    size_t index = getIndexFromPosition(position);
    if (index <= NUMBER_OF_TILES && index >= 0)
        tiles[0] = tileMap + index;
    if (index - WIDTH_OF_TILE_MAP <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP >= 0)
        tiles[1] = tileMap + index - WIDTH_OF_TILE_MAP;
    if (index + WIDTH_OF_TILE_MAP <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP >= 0)
        tiles[2] = tileMap + index + WIDTH_OF_TILE_MAP;
    if (index - 1 <= NUMBER_OF_TILES && index - 1 >= 0)
        tiles[3] = tileMap + index - 1;
    if (index + 1 <= NUMBER_OF_TILES && index + 1 >= 0)
        tiles[4] = tileMap + index + 1;
    if (index - WIDTH_OF_TILE_MAP - 1 <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP - 1 >= 0)
        tiles[5] = tileMap + index - WIDTH_OF_TILE_MAP - 1;
    if (index - WIDTH_OF_TILE_MAP + 1 <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP + 1 >= 0)
        tiles[6] = tileMap + index - WIDTH_OF_TILE_MAP + 1;
    if (index + WIDTH_OF_TILE_MAP - 1 <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP - 1 >= 0)
        tiles[7] = tileMap + index + WIDTH_OF_TILE_MAP - 1;
    if (index + WIDTH_OF_TILE_MAP + 1 <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP + 1 >= 0)
        tiles[8] = tileMap + index + WIDTH_OF_TILE_MAP + 1;
}

void TileMap::setTilesAroundPosition(Vector2 position, TILE_TYPE tile)
{
    TILE_TYPE *tiles[9] = {};
    getTilesAroundPosition(position, tiles);
    for (size_t i = 0; i < 9; i++)
        if (tiles[i] != NULL)
            *tiles[i] = tile;
    // size_t index = getIndexFromPosition(position);
    // if (index <= NUMBER_OF_TILES && index >= 0)
    //     tileMap[index] = tile;
    // if (index - WIDTH_OF_TILE_MAP <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP >= 0)
    //     tileMap[index - WIDTH_OF_TILE_MAP] = tile;
    // if (index + WIDTH_OF_TILE_MAP <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP >= 0)
    //     tileMap[index + WIDTH_OF_TILE_MAP] = tile;
    // if (index + 1 <= NUMBER_OF_TILES && index + 1 >= 0)
    //     tileMap[index + 1] = tile;
    // if (index - 1 <= NUMBER_OF_TILES && index - 1 >= 0)
    //     tileMap[index - 1] = tile;
    // if (index - WIDTH_OF_TILE_MAP + 1 <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP + 1 >= 0)
    //     tileMap[index - WIDTH_OF_TILE_MAP + 1] = tile;
    // if (index - WIDTH_OF_TILE_MAP - 1 <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP - 1 >= 0)
    //     tileMap[index - WIDTH_OF_TILE_MAP - 1] = tile;
    // if (index + WIDTH_OF_TILE_MAP + 1 <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP + 1 >= 0)
    //     tileMap[index + WIDTH_OF_TILE_MAP + 1] = tile;
    // if (index + WIDTH_OF_TILE_MAP - 1 <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP - 1 >= 0)
    //     tileMap[index + WIDTH_OF_TILE_MAP - 1] = tile;
}
