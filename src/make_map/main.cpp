#include <unistd.h>
#include <fcntl.h>
#include "../game/game_objects/tile_map/tile_map.hpp" // Includes tiles and other things.

int main(void)
{
    TILE_TYPE buffer[NUMBER_OF_TILES];
    for (size_t i = 0; i < NUMBER_OF_TILES; i++)
    {
        if (i < WIDTH_OF_TILE_MAP || i % WIDTH_OF_TILE_MAP == 0 || i % WIDTH_OF_TILE_MAP == WIDTH_OF_TILE_MAP - 1)
            buffer[i] = TILE_BOARDER;
        else if (i > NUMBER_OF_TILES - WIDTH_OF_TILE_MAP)
            buffer[i] = TILE_LOSE;
        else
            buffer[i] = TILE_AIR;
    }
    buffer[WIDTH_OF_TILE_MAP + 1] = TILE_SPAWN;

    int file = open("./map", O_CREAT | O_WRONLY);
    write(file, buffer, sizeof(buffer));
    close(file);
    return 0;
}