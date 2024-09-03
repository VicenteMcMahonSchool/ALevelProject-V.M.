#include "../enemy/enemy.hpp"
#include "./tile_map.hpp"
#include "../game_object/game_object.hpp"
#include <unistd.h>
#include <fcntl.h>

TileMap::TileMap(TILE_MAP_CONSTRUCTOR_ARGUMENTS) : GeneralGameObject(position), tileSize(tileSize)
{
#ifdef ONE_TILE_MAP
    if (tileFilesHaveBeenRead)
        return;
    tileFilesHaveBeenRead = true;
#endif
    int tileDataFile = open("./settings/tile_data", O_RDONLY);
    read(tileDataFile, &tileAttributesData, sizeof(tileAttributesData));
    close(tileDataFile);

    for (size_t i = 0; i < sizeof(tileAttributesData.tileData) / sizeof(TileAttributes); i++)
        if (tileAttributesData.tileData[i].display.type == TileDisplayData::TILE_DISPLAY_IMAGE)
            images[i] = IMG_LoadTexture(renderer, tileAttributesData.tileData[i].display.data.imageFile);
    int mapFile = open("./map", O_RDONLY);
    read(mapFile, tileMap, sizeof(tileMap));
    close(mapFile);
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
        rectangles[i].w = tileSize;
        rectangles[i].h = tileSize;
    }
}

TileMap::~TileMap()
{
    for (size_t i = 0; i < TILE_NORMAL_MAXIMUM_VALUE; i++)
        SDL_DestroyTexture(images[i]);
}

GETTER_AND_SETTER_CPP(unsigned int, TileMap, tileSize, TileSize)

const TILE_TYPE *TileMap::getSpawnTile(void)
{
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)

        if (tileMap[i] == TILE_SPAWN)
            return tileMap + i;
    return tileMap + WIDTH_OF_TILE_MAP + 1;
}

void TileMap::tick(void)
{
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        if (tileMap[i] == TILE_ROTATION)
        {
            TileCentres tileCentres = getTileCentresAroundPositionOfTile(tileMap + i);
            TilesAroundTile tiles = getTilesAroundIndex(i);
            if (tiles.right != NULL && tiles.bottomRight != NULL && tiles.bottom != NULL && tiles.bottomLeft != NULL && tiles.left != NULL && tiles.topLeft != NULL && tiles.top != NULL && tiles.topRight != NULL)
            {
                TILE_TYPE tileValue[8] = {*tiles.right, *tiles.bottomRight, *tiles.bottom, *tiles.bottomLeft, *tiles.left, *tiles.topLeft, *tiles.top, *tiles.topRight};
                setTileAtPosition(tileCentres.right, tileValue[7]);
                setTileAtPosition(tileCentres.bottomRight, tileValue[0]);
                setTileAtPosition(tileCentres.bottom, tileValue[1]);
                setTileAtPosition(tileCentres.bottomLeft, tileValue[2]);
                setTileAtPosition(tileCentres.left, tileValue[3]);
                setTileAtPosition(tileCentres.topLeft, tileValue[4]);
                setTileAtPosition(tileCentres.top, tileValue[5]);
                setTileAtPosition(tileCentres.topRight, tileValue[6]);
            }
        }
        if (tileMap[i] == TILE_ENEMY_SPAWNER && tileOutlines == false && numberOfTicks % 3 == 0)
        {
            Vector2 position = getCentrePositionOfTile(tileMap + i);
            GameObjectUnion *enemy = gameObjects.add(ENEMY);
            enemy->enemy = {position - (Vector2){(double)tileSize / 2, (double)tileSize / 2}};
        }
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
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
        rectangles[i].x -= cameraPosition.x - windowWidth / 2;
        rectangles[i].y -= cameraPosition.y - windowHeight / 2;
        if (rectangles[i].x > windowWidth)
        {
            i = (i / WIDTH_OF_TILE_MAP + 1) * WIDTH_OF_TILE_MAP - 1;
            continue;
        }
        else if (rectangles[i].x + (int)tileSize < 0)
        {
            double addedOn = (cameraPosition.x - position.x - windowWidth / 2) / (int)tileSize - 1;
            if (addedOn > 0)
                i += (size_t)addedOn;
            continue;
        }
        if (rectangles[i].y > windowHeight)
            break;
        else if (rectangles[i].y + (int)tileSize < 0)
        {
            long int addedOn = ((long int)(cameraPosition.y - position.y - (float)windowHeight / 2 + 1) / (long int)tileSize) * WIDTH_OF_TILE_MAP - 1;
            if (addedOn > 0)
                i += addedOn;
            continue;
        }
        TileAttributes tileAttributes = tileAttributesData.tileData[tileMap[i]];
        if (tileMap[i] == TILE_AIR || tileMap[i] == TILE_NONE || tileAttributes.display.visibleInEditorOnly && !tileOutlines)
            goto doNotFill;
        if (tileAttributes.display.type == TileDisplayData::TILE_DISPLAY_COLOUR)
        {
            SDL_SetRenderDrawColour(renderer, tileAttributes.display.data.colour.r, tileAttributes.display.data.colour.g, tileAttributes.display.data.colour.b, tileAttributes.display.data.colour.a);
            SDL_RenderFillRect(renderer, rectangles + i); // Fills the rectangle.
        }
        else if (tileAttributes.display.type == TileDisplayData::TILE_DISPLAY_IMAGE)
            SDL_RenderCopy(renderer, images[tileMap[i]], NULL, rectangles + i);
    doNotFill:
        if (tileOutlines)
        {
            SDL_SetRenderDrawColour(renderer, 0X22, 0X22, 0X22, 0XFF);
            SDL_RenderDrawRect(renderer, rectangles + i);
        }
    }
    GeneralGameObject::draw();
}
void TileMap::drawShadows(void)
{
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        TILE_MAP_RECTANGLES_POSITION
        rectangles[i].x = (int)round((double)rectangles[i].x - cameraPosition.x + (double)windowWidth / 2);
        rectangles[i].y = (int)round((double)rectangles[i].y - cameraPosition.y + (double)windowHeight / 2);
        if (rectangles[i].x > windowWidth)
        {
            i = (i / WIDTH_OF_TILE_MAP + 1) * WIDTH_OF_TILE_MAP - 1;
            continue;
        }
        else if (rectangles[i].x + (int)tileSize < 0)
        {
            double addedOn = (cameraPosition.x - position.x - windowWidth / 2) / (int)tileSize - 1;
            if (addedOn > 0)
                i += (size_t)addedOn;
            continue;
        }
        if (rectangles[i].y > windowHeight)
            break;
        else if (rectangles[i].y + (int)tileSize < 0)
        {
            long int addedOn = ((long int)(cameraPosition.y - position.y - (float)windowHeight / 2 + 1) / (long int)tileSize) * WIDTH_OF_TILE_MAP - 1;
            if (addedOn > 0)
                i += addedOn;
            continue;
        }
        if (tileMap[i] == TILE_AIR || tileMap[i] == TILE_NONE || (tileAttributesData.tileData[tileMap[i]].display.visibleInEditorOnly && !tileOutlines))
            continue;
        SDL_Rect shadowRectangle{rectangles[i].x, rectangles[i].y, rectangles[i].w + SHADOW_DISTANCE_X, rectangles[i].h + SHADOW_DISTANCE_Y};
        SDL_SetRenderDrawColour(renderer, 0X11, 0X11, 0X11, 0XFF);
        SDL_RenderFillRect(renderer, &shadowRectangle); // Fills the rectangle.
    }
}

void TileMap::saveMap(void)
{
    FILE *file = fopen("./map", "wb");
    fwrite(tileMap, sizeof(TILE_TYPE), NUMBER_OF_TILES, file);
    fclose(file);
}

void TileMap::resetRemovedCoins(void)
{
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
        if (tileMap[i] == TILE_COIN_DELETED)
            tileMap[i] = TILE_COIN;
}

size_t TileMap::getTileIndex(const TILE_TYPE *tile)
{
    return tile - tileMap;
}

void TileMap::setTileAtIndex(size_t tileIndex, TILE_TYPE tileType)
{
    if (tileIndex >= NUMBER_OF_TILES || tileIndex < 0)
        return;
    if (tileType == TILE_SPAWN)
    {
        // This loop makes sure that there will only be one spawn tile.
        for (size_t i = 0; i < NUMBER_OF_TILES; i++)
            if (tileMap[i] == TILE_SPAWN)
                tileMap[i] = TILE_AIR;
    }
    tileMap[tileIndex] = tileType;
}

void TileMap::setTileAtPosition(Vector2 position, TILE_TYPE tileType)
{
    setTileAtIndex(getIndexFromPosition(position), tileType);
}
void TileMap::setTilesAroundPosition(Vector2 position, TILE_TYPE tileType, size_t distance)
{
    if (distance == 1)
        return setTileAtPosition(position, tileType);
    if (tileType == TILE_SPAWN) // Avoids situation with multiple spawn tiles.
        tileType = TILE_AIR;
    size_t index = getIndexFromPosition(position);
    size_t topCornerDifference = distance / 2 + WIDTH_OF_TILE_MAP * (distance / 2); // Avoids integer underflow.
    size_t topIndex = 0;
    if (index >= topCornerDifference)
        topIndex = index - topCornerDifference;
    else if (index >= distance)
        topIndex = index - distance / 2;
    for (size_t i = 0; i < distance; i++)
        for (size_t j = 0; j < distance; j++)
        {
            size_t currentIndex = topIndex + i + j * WIDTH_OF_TILE_MAP;
            if (currentIndex > NUMBER_OF_TILES)
                continue;
            tileMap[currentIndex] = tileType;
        }
}

size_t TileMap::getIndexFromPosition(Vector2 position)
{
    return (size_t)round(position.y) / tileSize * WIDTH_OF_TILE_MAP + (size_t)round(position.x) / tileSize;
}

const TILE_TYPE *TileMap::getTileAtPosition(Vector2 position)
{
    size_t index = getIndexFromPosition(position);
    if (index > NUMBER_OF_TILES || index < 0)
        return NULL;
    return tileMap + index;
}

TilesAroundTile TileMap::getTilesAroundIndex(size_t index)
{
    TilesAroundTile tiles;
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

TilesAroundTile TileMap::getTilesAroundPosition(Vector2 position)
{
    size_t index = getIndexFromPosition(position);
    return getTilesAroundIndex(index);
}

Vector2 TileMap::getCentrePositionOfTile(const TILE_TYPE *tile)
{
    if (tile == NULL)
        return {(double)tileSize, (double)tileSize};
    size_t tileIndex = tile - tileMap;
    return {
        (tileIndex % WIDTH_OF_TILE_MAP) * tileSize + (double)tileSize / 2,
        tileIndex / WIDTH_OF_TILE_MAP * (tileSize) + (double)tileSize / 2};
}

TileCentres TileMap::getTileCentresAroundPositionOfTile(const TILE_TYPE *tile)
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

TileAttributes &TileMap::getTileAttributes(const TILE_TYPE tile)
{
    return tileAttributesData.tileData[tile];
}
TileAttributes &TileMap::getTileAttributes(const TILE_TYPE *tilePointer)
{
    if (tilePointer == NULL)
        return getTileAttributes(TILE_AIR);
    return getTileAttributes(*tilePointer);
}