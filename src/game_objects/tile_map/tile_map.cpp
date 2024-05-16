#include "./tile_map.hpp"

TileMap::TileMap(Vector2 position, unsigned int tileSize) : GeneralGameObject(position), tileSize(tileSize)
{
    this->numberOfTiles = (unsigned int)ceil(((double)windowWidth * (double)windowHeight) / (tileSize * tileSize)) /*135*/;
    this->tileMap = (TILE_TYPE *)calloc(this->numberOfTiles, sizeof(TILE_TYPE));
    this->rectangles = (SDL_Rect *)calloc(this->numberOfTiles, sizeof(SDL_Rect));
    for (unsigned int i = 0; i < this->numberOfTiles; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
        this->rectangles[i].w = tileSize;
        this->rectangles[i].h = tileSize;
    }
    printf("Window width: %u, Window height: %u, Tile size: %u, Number of tiles: %u\n", windowWidth, windowHeight, tileSize, this->numberOfTiles);
}
TileMap::~TileMap()
{
    free(this->rectangles);
    free(this->tileMap);
}
void TileMap::update(double deltaTime)
{
    for (unsigned int i = 0; i < this->numberOfTiles; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
    }
}
void TileMap::draw(void)
{
    // SDL_SetRenderDrawColour(renderer, this->colour.r, this->colour.g, this->colour.b, this->colour.a); // Sets draw colour.
    for (unsigned int i = 0; i < this->numberOfTiles; i++)
    {
        if (this->tileMap[i] == TILE_AIR)
            SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0X00);
        else if (this->tileMap[i] == TILE_PLATFORM)
            SDL_SetRenderDrawColour(renderer, 0X33, 0XDD, 0X33, 0XFF);
        SDL_RenderFillRect(renderer, this->rectangles + i); // Fill rectangle.
    }
    GeneralGameObject::draw();
}