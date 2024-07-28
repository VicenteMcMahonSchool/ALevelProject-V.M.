#include "./tile_map.hpp"

GETTER_AND_SETTER_CPP(unsigned int, TileMap, tileSize, TileSize)
TileMap::TileMap(Vector2 position, unsigned int tileSize) : GeneralGameObject(position), tileSize(tileSize)
{
    FILE *file = fopen("./map", "rb");
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);
    if (fileSize != sizeof(tileMap))
        throw std::runtime_error("File size of map file is incorrect.");
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
        rectangles[i].w = tileSize;
        rectangles[i].h = tileSize;
        fread(tileMap + i, sizeof(TILE_TYPE), 1, file);
    }
    fclose(file);
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
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        rectangles[i].x -= cameraPosition.x - windowWidth / 2;
        rectangles[i].y -= cameraPosition.y - windowHeight / 2;
        SDL_Rect shadowRectangle{rectangles[i].x + SHADOW_DISTANCE_X, rectangles[i].y + SHADOW_DISTANCE_Y, rectangles[i].w, rectangles[i].h};
        if (tileMap[i] == TILE_AIR || tileMap[i] == TILE_NONE)
            goto doNotFill;
        SDL_SetRenderDrawColour(renderer, 0X11, 0X11, 0X11, 0XFF);
        SDL_RenderFillRect(renderer, &shadowRectangle); // Fills the rectangle.
        if (tileMap[i] == TILE_PLATFORM)
        {
            SDL_SetRenderDrawColour(renderer, 0X55, 0X77, 0X77, 0XFF);
        }
        else if (tileMap[i] == TILE_BOARDER)
        {
            SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X77, 0XFF);
        }
        else if (tileMap[i] == TILE_WIN)
        {
            SDL_SetRenderDrawColour(renderer, 0X33, 0X77, 0X33, 0XFF);
        }
        else if (tileMap[i] == TILE_LOSE)
        {
            SDL_SetRenderDrawColour(renderer, 0X77, 0X33, 0X33, 0XFF);
        }
        SDL_RenderFillRect(renderer, rectangles + i); // Fills the rectangle.
    doNotFill:
        if (tileOutlines)
        {
            SDL_SetRenderDrawColour(renderer, 0XDD, 0X00, 0X00, 0X00);
            SDL_RenderDrawRect(renderer, rectangles + i);
        }
        // rectangles[i].x += cameraPosition.x - windowWidth / 2;
        // rectangles[i].y += cameraPosition.y - windowHeight / 2;
    }
    GeneralGameObject::draw();
}

void TileMap::saveMap(void)
{
    FILE *file = fopen("./map", "wb");
    fwrite(tileMap, sizeof(TILE_TYPE), NUMBER_OF_TILES, file);
    fclose(file);
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

TilesAroundPosition TileMap::getTilesAroundPosition(Vector2 position)
{
    size_t index = getIndexFromPosition(position);
    TilesAroundPosition tiles;
    if (index <= NUMBER_OF_TILES && index >= 0)
        tiles.centre = tileMap + index;
    if (index - WIDTH_OF_TILE_MAP <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP >= 0)
        tiles.top = tileMap + index - WIDTH_OF_TILE_MAP;
    if (index + WIDTH_OF_TILE_MAP <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP >= 0)
        tiles.bottom = tileMap + index + WIDTH_OF_TILE_MAP;
    if (index - 1 <= NUMBER_OF_TILES && index - 1 >= 0)
        tiles.left = tileMap + index - 1;
    if (index + 1 <= NUMBER_OF_TILES && index + 1 >= 0)
        tiles.right = tileMap + index + 1;
    if (index - WIDTH_OF_TILE_MAP - 1 <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP - 1 >= 0)
        tiles.topLeft = tileMap + index - WIDTH_OF_TILE_MAP - 1;
    if (index - WIDTH_OF_TILE_MAP + 1 <= NUMBER_OF_TILES && index - WIDTH_OF_TILE_MAP + 1 >= 0)
        tiles.topRight = tileMap + index - WIDTH_OF_TILE_MAP + 1;
    if (index + WIDTH_OF_TILE_MAP - 1 <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP - 1 >= 0)
        tiles.bottomLeft = tileMap + index + WIDTH_OF_TILE_MAP - 1;
    if (index + WIDTH_OF_TILE_MAP + 1 <= NUMBER_OF_TILES && index + WIDTH_OF_TILE_MAP + 1 >= 0)
        tiles.bottomRight = tileMap + index + WIDTH_OF_TILE_MAP + 1;
    return tiles;
}

void TileMap::setTilesAroundPosition(Vector2 position, TILE_TYPE tile)
{
    TilesAroundPosition tiles = getTilesAroundPosition(position);
    if (tiles.centre)
        *tiles.centre = tile;
    if (tiles.left != NULL)
        *tiles.left = tile;
    if (tiles.right != NULL)
        *tiles.right = tile;
    if (tiles.top != NULL)
        *tiles.top = tile;
    if (tiles.bottom != NULL)
        *tiles.bottom = tile;
    if (tiles.topLeft != NULL)
        *tiles.topLeft = tile;
    if (tiles.topRight != NULL)
        *tiles.topRight = tile;
    if (tiles.bottomLeft != NULL)
        *tiles.bottomLeft = tile;
    if (tiles.bottomRight != NULL)
        *tiles.bottomRight = tile;
}

Vector2 TileMap::getCentrePositionOfTile(TILE_TYPE *tile)
{
    size_t tileIndex = tile - tileMap;
    return {
        (tileIndex % WIDTH_OF_TILE_MAP) * tileSize + (double)tileSize / 2,
        tileIndex / WIDTH_OF_TILE_MAP * (tileSize) + (double)tileSize / 2};
}

TileCentres TileMap::getTileCentresAroundPositionOfTile(TILE_TYPE *tile)
{
    TileCentres output;
    output.centre = getCentrePositionOfTile(tile);
    output.left = output.centre + Vector2{-(double)tileSize, 0};
    output.right = output.centre + Vector2{(double)tileSize, 0};
    output.topLeft = output.centre + Vector2{-(double)tileSize, -(double)tileSize};
    output.top = output.centre + Vector2{0, -(double)tileSize};
    output.topRight = output.centre + Vector2{(double)tileSize, -(double)tileSize};
    output.bottomLeft = output.centre + Vector2{-(double)tileSize, (double)tileSize};
    output.bottom = output.centre + Vector2{0, (double)tileSize};
    output.bottomRight = output.centre + Vector2{(double)tileSize, (double)tileSize};
    return output;
}

TileAttributes getTileAttributes(TILE_TYPE tile)
{
    TileAttributes output{};
    if (tile == TILE_PLATFORM || tile == TILE_BOARDER)
        output.isCollidable = true;
    else
        output.isCollidable = false;
    return output;
}
TileAttributes getTileAttributes(TILE_TYPE *tilePointer)
{
    if (tilePointer == NULL)
        return getTileAttributes(TILE_AIR);
    return getTileAttributes(*tilePointer);
}