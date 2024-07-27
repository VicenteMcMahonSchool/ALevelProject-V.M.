#include "./application.hpp"

int windowWidth, windowHeight;
SDL_Window *window;
SDL_Renderer *renderer;
LinkedList /* <GameObject> */ gameObjects{};
TileMap tileMap = TileMap({0, 0}, 120);
Vector2 cameraPosition{0, 0};
TTF_Font *font = NULL;

// Constructor for application, this is used to make the class.
Application::Application()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error(SDL_GetError());
    if (TTF_Init() < 0)
        throw std::runtime_error(TTF_GetError());
    SDL_DisplayMode displayMode{};
    if (SDL_GetCurrentDisplayMode(0, &displayMode))
        throw std::runtime_error(SDL_GetError()); // Gets data about the display.
    font = TTF_OpenFont("OpenSans-VariableFont_wdth,wght.ttf", 256);
    if (font == NULL)
        throw std::runtime_error(TTF_GetError());
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
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

// This is the main loop for the game.
void Application::gameScreen(SCREEN *screen)
{
    gameObjects.makeEmpty();
    unsigned int tileSize = tileMap.getTileSize();
    Player player{{(double)tileSize, (double)tileSize}};
    gameObjects.add({&player});
    gameObjects.add({&tileMap});
    // tileMap.setTile(2, 4, TILE_PLATFORM);
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
    unsetAllKeys();
    *screen = SCREEN_MENU;
    return;
}

void Application::drawText(const char *text, SDL_Rect *rectangle)
{
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, {0X00, 0X00, 0X00});
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_RenderCopy(renderer, textTexture, NULL, rectangle);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
void Application::drawText(const char *text, SDL_Rect rectangle)
{
    drawText(text, &rectangle);
}

void Application::menuScreen(SCREEN *screen)
{
    *screen = SCREEN_EXIT;
    cameraPosition = {0, 0};
    constexpr int widthOfButton = 256, heightOfButton = 128;
    Rectangle button{{-widthOfButton / 2, -heightOfButton / 2}, {0X77, 0X77, 0X77, 0XFF}, widthOfButton, heightOfButton};
    SDL_Event event;
    SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0XFF);
    SDL_RenderClear(renderer);
    button.update(0);
    button.draw();
    SDL_Rect buttonRectangle = button.getRectangle();
    drawText("Play", buttonRectangle);
    SDL_RenderPresent(renderer);
    while (true)
    {
        while (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
                goto exit;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_P:
                    *screen = SCREEN_GAME;
                    goto exit;
                case SDL_SCANCODE_ESCAPE: // If the escape key is pressed, exit.
                    goto exit;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x > buttonRectangle.x && x < buttonRectangle.x + buttonRectangle.w && y > buttonRectangle.y && y < buttonRectangle.y + buttonRectangle.h)
                {
                    *screen = SCREEN_GAME;
                    goto exit;
                }
                break;
            }
        }
        SDL_Delay(16);
    }
exit:
    return;
}

void Application::run(void)
{
    SCREEN screen = SCREEN_MENU;
    while (screen != SCREEN_EXIT)
    {
        if (screen == SCREEN_MENU)
            menuScreen(&screen);
        else if (screen == SCREEN_GAME)
            gameScreen(&screen);
    }
}