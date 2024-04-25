#include "./application/application.hpp"

Application application{128, 128};
// The main function, needed to start the program.
int main(void)
{
    // Starts the application.
    application.run();
    return 0; // 0 signifies that there are no errors.
}
