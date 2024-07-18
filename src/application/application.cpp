#include "./application.hpp"

int windowWidth, windowHeight;
SDL_Window *window;
SDL_Renderer *renderer;
LinkedList /* <GameObject> */ gameObjects{};
TileMap tileMap = TileMap({0, 0}, 120);
Vector2 cameraPosition{0, 0};

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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        throw std::runtime_error(SDL_GetError());
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;
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
    Player player{{0, 0}};
    gameObjects.add({&player});
    gameObjects.add({&tileMap});
    SDL_Texture *imageTexture = IMG_LoadTexture(renderer, "image.jpg");
    SDL_Event event;
    // Delta Time code taken from https://gamedev.stackexchange.com/questions/110825/how-to-calculate-delta-time-with-sdl.
    Uint64 now = SDL_GetPerformanceCounter(), last = 0; // Will be used to calculate 'deltaTime'.
    double deltaTime = 0;
    while (true)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
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
                default:
                    setKeyDown(event.key.keysym.scancode);
                    break;
                }
                break;
            case SDL_KEYUP:
                unsetKeyDown(event.key.keysym.scancode);
                break;
            case SDL_QUIT: // Quit event.
                goto exit;
            }
        }
        SDL_RenderCopy(renderer, imageTexture, NULL, NULL);
        // SDL_RenderPresent(renderer);
        // SDL_RenderClear(renderer);                                            // Clears the screen.
        TRAVERSE(gameObjects.head, GameObject, item->datum.update(deltaTime)) // Updates all the 'GameObjects'.
        cameraPosition = player.getPosition() + (Vector2){(double)player.getRectangle().w / 2, (double)player.getRectangle().h / 2};
        TRAVERSE(gameObjects.head, GameObject, item->datum.draw()) // Draws all the 'GameObjects'.
        // SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0XFF);            // Sets the colour.
        SDL_RenderPresent(renderer); // Renders everything.
        SDL_Delay(16);
    }
exit: // This is a section which can be reached using 'goto' statements.
    SDL_DestroyTexture(imageTexture);
    return;
}