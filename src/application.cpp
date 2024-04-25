#include "./application.hpp"

// Constructor for application, this is used to make the class.
Application::Application(unsigned int windowWidth, unsigned int windowHeight)
{
    this->window = SDL_CreateWindow(
        "Platformer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        throw SDL_GetError();
    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!this->renderer)
        throw SDL_GetError();
}

// Destructor for application, this is used to free memory.
Application::~Application()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

// This is going to be the main loop for the code.
void Application::run(void)
{
    while (true)
    {
        SDL_Event event;
        /*
        Loops until there is an error getting the event. The 'event' variable is passed by reference to 'SDL_PollEvent',
        this function will get the current event and store it in 'event'.
        */
        while (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                goto exit;
            }
        }
        SDL_RenderClear(this->renderer);                                // Clears the screen.
        SDL_SetRenderDrawColor(this->renderer, 0X33, 0X33, 0X33, 0XFF); // Sets the colour.
        SDL_RenderPresent(this->renderer);                              // Renders everything.
        SDL_Delay(128);
    }
exit: // This is a section which can be reached using 'goto' statements.
    return;
}