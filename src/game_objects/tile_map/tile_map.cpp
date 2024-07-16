#include "./tile_map.hpp"

TileMap::TileMap(Vector2 position, unsigned int tileSize) : GeneralGameObject(position), tileSize(tileSize)
{
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
        this->rectangles[i].w = tileSize;
        this->rectangles[i].h = tileSize;
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
    // SDL_SetRenderDrawColour(renderer, this->colour.r, this->colour.g, this->colour.b, this->colour.a); // Sets draw colour.
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        if (this->tileMap[i] == TILE_AIR)
            SDL_SetRenderDrawColour(renderer, 0XDD, 0X00, 0X00, 0X00);
        else if (this->tileMap[i] == TILE_PLATFORM)
        {
            // SDL_SetRenderDrawColour(renderer, 0X33, 0XDD, 0X33, 0XFF);
            SDL_SetRenderDrawColour(renderer, 0X77, 0X33, 0X33, 0XFF);
            SDL_RenderFillRect(renderer, this->rectangles + i); // Fill rectangle.
        }
        SDL_RenderDrawRect(renderer, this->rectangles + i);
    }
    GeneralGameObject::draw();
}

void TileMap::setTile(size_t x, size_t y, TILE_TYPE tileType)
{
    this->tileMap[y * WIDTH_OF_TILE_MAP + x % WIDTH_OF_TILE_MAP] = tileType;
}

size_t TileMap::getIndexFromPosition(Vector2 position)
{
    return (size_t)(position.y) / this->tileSize * WIDTH_OF_TILE_MAP + (size_t)(position.x) / tileSize;
}

TILE_TYPE *TileMap::getTileAtPosition(Vector2 position)
{
    size_t index = getIndexFromPosition(position);
    if (index > NUMBER_OF_TILES || index < 0)
        return NULL;
    return this->tileMap + index;
}

void TileMap::getTilesAroundPosition(Vector2 position, TILE_TYPE *tiles[9])
{
    size_t index = getIndexFromPosition(position);
    if (index <= NUMBER_OF_TILES && index >= 0)
        tiles[0] = this->tileMap + index;
    if (index - WIDTH_OF_TILE_MAP <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP >= 0)
        tiles[1] = this->tileMap + index - WIDTH_OF_TILE_MAP;
    if (index + WIDTH_OF_TILE_MAP <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP >= 0)
        tiles[2] = this->tileMap + index + WIDTH_OF_TILE_MAP;
    if (index - 1 <= NUMBER_OF_TILES && index - 1 >= 0)
        tiles[3] = this->tileMap + index - 1;
    if (index + 1 <= NUMBER_OF_TILES && index + 1 >= 0)
        tiles[4] = this->tileMap + index + 1;
    if (index - WIDTH_OF_TILE_MAP - 1 <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP - 1 >= 0)
        tiles[5] = this->tileMap + index - WIDTH_OF_TILE_MAP - 1;
    if (index - WIDTH_OF_TILE_MAP + 1 <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP + 1 >= 0)
        tiles[6] = this->tileMap + index - WIDTH_OF_TILE_MAP + 1;
    if (index + WIDTH_OF_TILE_MAP - 1 <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP - 1 >= 0)
        tiles[7] = this->tileMap + index + WIDTH_OF_TILE_MAP - 1;
    if (index + WIDTH_OF_TILE_MAP + 1 <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP + 1 >= 0)
        tiles[8] = this->tileMap + index + WIDTH_OF_TILE_MAP + 1;
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
    //     this->tileMap[index] = tile;
    // if (index - WIDTH_OF_TILE_MAP <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP >= 0)
    //     this->tileMap[index - WIDTH_OF_TILE_MAP] = tile;
    // if (index + WIDTH_OF_TILE_MAP <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP >= 0)
    //     this->tileMap[index + WIDTH_OF_TILE_MAP] = tile;
    // if (index + 1 <= NUMBER_OF_TILES && index + 1 >= 0)
    //     this->tileMap[index + 1] = tile;
    // if (index - 1 <= NUMBER_OF_TILES && index - 1 >= 0)
    //     this->tileMap[index - 1] = tile;
    // if (index - WIDTH_OF_TILE_MAP + 1 <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP + 1 >= 0)
    //     this->tileMap[index - WIDTH_OF_TILE_MAP + 1] = tile;
    // if (index - WIDTH_OF_TILE_MAP - 1 <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP - 1 >= 0)
    //     this->tileMap[index - WIDTH_OF_TILE_MAP - 1] = tile;
    // if (index + WIDTH_OF_TILE_MAP + 1 <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP + 1 >= 0)
    //     this->tileMap[index + WIDTH_OF_TILE_MAP + 1] = tile;
    // if (index + WIDTH_OF_TILE_MAP - 1 <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP - 1 >= 0)
    //     this->tileMap[index + WIDTH_OF_TILE_MAP - 1] = tile;
}
