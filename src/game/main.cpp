#include "./application/application.hpp"

// The main function, needed to start the program.
int main(void)
{
    // TileAttributes test{};
    // test.display.type = test.display.TILE_DISPLAY_COLOUR;
    // test.display.datum.colour = {0X00, 0X00, 0X00, 0XFF};
    // test.isCollidable = test.isCollisionDetectable = true;
    // for (size_t i = 0; i < sizeof(test); i++)
    //     printf("%02x ", ((unsigned char *)&test)[i]);
    // puts("");
    // Starts the application.
    application.run();
    return 0; // 0 signifies that there are no errors.
}
