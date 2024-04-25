#include "./application.hpp"

// Constructor for application, this is used to make the class.
Application::Application()
{
    SDL_GetCurrentDisplayMode(0, &displayMode); // Gets data about the display.
    this->window = SDL_CreateWindow(
        "Platformer",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        displayMode.w, displayMode.h,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (this->window == NULL)
        throw std::runtime_error(SDL_GetError());
    SDL_SetWindowFullscreen(this->window, SDL_WINDOW_FULLSCREEN); // Makes the window fullscreen.
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!this->renderer)
        throw std::runtime_error(SDL_GetError());
}

// Destructor for application, this is used to free memory.
Application::~Application()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

// This is the main loop for the code.
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
        SDL_SetRenderDrawColor(this->renderer, 0XFF, 0XFF, 0XFF, 0XFF); // Sets draw colour.
        SDL_RenderFillRect(this->renderer, &testRectangle);             // Fills rectangle.
        SDL_SetRenderDrawColor(this->renderer, 0X33, 0X33, 0X33, 0XFF); // Sets the colour.
        SDL_RenderPresent(this->renderer);                              // Renders everything.
        SDL_Delay(128);
    }
exit: // This is a section which can be reached using 'goto' statements.
    return;
}