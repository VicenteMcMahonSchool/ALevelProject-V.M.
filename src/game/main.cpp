#define SDL_MAIN_HANDLED
#include "./application/application.hpp"

// The main function, needed to start the program.
int main(void) {
    // Starts the application.
    application.run();
    return 0; // 0 signifies that there are no errors.
}
