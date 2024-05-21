#include "./tile_map.hpp"

TileMap::TileMap(Vector2 position, unsigned int tileSize) : GeneralGameObject(position), tileSize(tileSize)
{
    for (unsigned int i = 0; i < NUMBER_OF_TILES; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
        this->rectangles[i].w = tileSize;
        this->rectangles[i].h = tileSize;
    }
}
void TileMap::update(double deltaTime)
{
    for (unsigned int i = 0; i < NUMBER_OF_TILES; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
    }
}
void TileMap::draw(void)
{
    // SDL_SetRenderDrawColour(renderer, this->colour.r, this->colour.g, this->colour.b, this->colour.a); // Sets draw colour.
    for (unsigned int i = 0; i < NUMBER_OF_TILES; i++)
    {
        // if (i % 3 == 0)
        //     SDL_SetRenderDrawColour(renderer, 0XFF, 0X33, 0X33, 0X00);
        // else if (i % 3 == 1)
        //     SDL_SetRenderDrawColour(renderer, 0X33, 0XFF, 0X33, 0X00);
        // else if (i % 3 == 2)
        //     SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0XFF, 0X00);
        if (this->tileMap[i] == TILE_AIR)
            SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0X00);
        else if (this->tileMap[i] == TILE_PLATFORM)
            SDL_SetRenderDrawColour(renderer, 0X33, 0XDD, 0X33, 0XFF);
        SDL_RenderFillRect(renderer, this->rectangles + i); // Fill rectangle.
    }
    GeneralGameObject::draw();
}

void TileMap::setTile(unsigned int x, unsigned int y, TILE_TYPE tileType)
{
    this->tileMap[y * WIDTH_OF_TILE_MAP + x % WIDTH_OF_TILE_MAP] = tileType;
}
