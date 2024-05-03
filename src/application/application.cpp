#include "./application.hpp"
#include "../linked_list/linked_list.hpp"

SDL_Window *window;
SDL_Renderer *renderer;
LinkedList<GameObject> gameObjects{};

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
        SDL_WINDOW_SHOWN);
    if (window == NULL)
        throw std::runtime_error(SDL_GetError());
    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN); // Makes the window fullscreen.
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

void Application::updateGameObject(GameObject *gameObject, double deltaTime)
{
    switch (gameObject->type)
    {
    case RECTANGLE:
        gameObject->value.rectangle.update(deltaTime);
        break;
    case MOVABLE_RECTANGLE:
        gameObject->value.movableRectangle.update(deltaTime);
        break;
    }
}

void Application::drawGameObject(GameObject *gameObject)
{
    switch (gameObject->type)
    {
    case RECTANGLE:
        gameObject->value.rectangle.draw();
        break;
    case MOVABLE_RECTANGLE:
        gameObject->value.movableRectangle.draw();
        break;
    }
}

// This is the main loop for the code.
void Application::run(void)
{
    gameObjects.add({.type = MOVABLE_RECTANGLE, .value = MovableRectangle({0, 0}, {0XFF, 0XFF, 0XFF, 0XFF}, 128, 128)});
    gameObjects.add({.type = RECTANGLE, .value = Rectangle({1000, 1000}, {0X33, 0X33, 0XFF, 0XFF}, 128, 128)});
    TRAVERSE(gameObjects.head, GameObject, if (item->datum.type == MOVABLE_RECTANGLE) item->datum.value.movableRectangle.setVelocity({16, 0}))
    while (true)
    {
        SDL_Event event;
        // Delta Time code taken from https://gamedev.stackexchange.com/questions/110825/how-to-calculate-delta-time-with-sdl.
        Uint64 now = SDL_GetPerformanceCounter(), last = 0; // Will be used to calculate 'deltaTime'.
        double deltaTime = 0;
        /*
        Loops until there is an error getting the event. The 'event' variable is passed by reference to 'SDL_PollEvent',
        this function will get the current event and store it in 'event'.
        */
        while (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE: // If the escape key is pressed, exit.
                    goto exit;
                    break;
                }
                break;
            case SDL_QUIT: // Quit event.
                goto exit;
            }
            last = now;
            now = SDL_GetPerformanceCounter();
            deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
            SDL_RenderClear(renderer);                                                              // Clears the screen.
            TRAVERSE(gameObjects.head, GameObject, this->updateGameObject(&item->datum, deltaTime)) // Updates all the rectangles.
            TRAVERSE(gameObjects.head, GameObject, this->drawGameObject(&item->datum))              // Draws all the rectangles.
            SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0XFF);                              // Sets the colour.
            SDL_RenderPresent(renderer);                                                            // Renders everything.
            SDL_Delay(16);
        }
    }
exit: // This is a section which can be reached using 'goto' statements.
    return;
}