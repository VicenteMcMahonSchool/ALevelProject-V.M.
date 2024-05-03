#include "./application.hpp"
#include "../linked_list/linked_list.hpp"

SDL_Window *window;
SDL_Renderer *renderer;
LinkedList<Rectangle> rectangles{};

// Constructor for application, this is used to make the class.
Application::Application()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(SDL_GetError());
    SDL_DisplayMode displayMode{};
    if (SDL_GetCurrentDisplayMode(0, &displayMode))
        throw std::runtime_error(SDL_GetError()); // Gets data about the display.
    window = SDL_CreateWindow(
        "Platformer",
        SDL_WINDOWPOS_CENTRED, SDL_WINDOWPOS_CENTRED,
        displayMode.w, displayMode.h,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == NULL)
        throw std::runtime_error(SDL_GetError());
    // SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); // Makes the window fullscreen.
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer)
        throw std::runtime_error(SDL_GetError());
}

// Destructor for application, this is used to free memory.
Application::~Application()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// This is the main loop for the code.
void Application::run(void)
{
    rectangles.add(Rectangle({0, 0}, {0XFF, 0XFF, 0XFF, 0XFF}, 128, 128));
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
            case SDL_QUIT: // Quit event.
                goto exit;
            }
        }
        SDL_RenderClear(renderer);                                 // Clears the screen.
        TRAVERSE(rectangles.head, Rectangle, item->datum.draw())   // Draws all the rectangles.
        SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0XFF); // Sets the colour.
        SDL_RenderPresent(renderer);                               // Renders everything.
        SDL_Delay(128);
    }
exit: // This is a section which can be reached using 'goto' statements.
    return;
}