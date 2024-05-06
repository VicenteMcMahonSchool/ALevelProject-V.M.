#include "./tile_map.hpp"

TileMap::TileMap(Vector2 position, SDL_Colour colour, unsigned int tileSize) : GeneralGameObject(position), colour(colour), tileSize(tileSize)
{
    this->numberOfTiles = (unsigned int)(windowWidth * (double)windowHeight / tileSize / tileSize);
    this->tileMap = (TILE_TYPE *)calloc(this->numberOfTiles, sizeof(TILE_TYPE));
    this->rectangles = (SDL_Rect *)calloc(this->numberOfTiles, sizeof(SDL_Rect));
    for (unsigned int i = 0; i < this->numberOfTiles; i++)
    {
        this->rectangles[i].x = (i % windowHeight) * tileSize;
        this->rectangles[i].y = (i / windowHeight) * tileSize;
        this->rectangles[i].w = tileSize;
        this->rectangles[i].h = tileSize;
    }
}
TileMap::~TileMap()
{
    free(this->tileMap);
}
void TileMap::update(double deltaTime)
{
    this->position.x += 1 * deltaTime;
    for (unsigned int i = 0; i < this->numberOfTiles; i++)
    {
        this->rectangles[i].x = (i % windowHeight) * tileSize - this->position.x;
        this->rectangles[i].y = (i / windowHeight) * tileSize - this->position.y;
    }
}
void TileMap::draw(void)
{
    // SDL_SetRenderDrawColour(renderer, this->colour.r, this->colour.g, this->colour.b, this->colour.a); // Sets draw colour.
    for (unsigned int i = 0; i < this->numberOfTiles; i++)
    {
        if (i % 3 == 0)
            SDL_SetRenderDrawColour(renderer, 0XFF, 0X00, 0X00, 0XFF);
        else if (i % 3 == 1)
            SDL_SetRenderDrawColour(renderer, 0X00, 0XFF, 0X00, 0XFF);
        else
            SDL_SetRenderDrawColour(renderer, 0X00, 0X00, 0XFF, 0XFF);
        SDL_RenderFillRect(renderer, this->rectangles + i); // Fill rectangle.
    }
    GeneralGameObject::draw();
}