#include "./application.hpp"

int windowWidth, windowHeight;
SDL_Window *window;
SDL_Renderer *renderer;
LinkedList /* <GameObject> */ gameObjects{};
TileMap tileMap = TileMap({0, 0}, 120);
Vector2 cameraPosition{0, 0};
TTF_Font *font = NULL;
SCREEN screen = SCREEN_MENU;

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
void Application::gameScreen(void)
{
    gameObjects.makeEmpty();
    unsigned int tileSize = tileMap.getTileSize();
    tileMap.tileOutlines = false;
    Player player{tileMap.getCentrePositionOfTile(tileMap.getSpawnTile()) - (Vector2){(double)tileSize / 2, (double)tileSize / 2}};
    gameObjects.add({&tileMap});
    gameObjects.add({&player});
    SDL_Event event;
    // Delta Time code taken from https://gamedev.stackexchange.com/questions/110825/how-to-calculate-delta-time-with-sdl.
    Uint64 now = SDL_GetPerformanceCounter(), last = 0; // Will be used to calculate 'deltaTime'.
    double deltaTime = 0;
    while (screen == SCREEN_GAME)
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
        SDL_SetRenderDrawColour(renderer, 0X55, 0X55, 0X55, 0XFF);
        SDL_RenderClear(renderer);                                            // Clears the screen.
        TRAVERSE(gameObjects.head, GameObject, item->datum.update(deltaTime)) // Updates all the 'GameObjects'.
        cameraPosition = player.getPosition() + (Vector2){(double)player.getRectangle().w / 2, (double)player.getRectangle().h / 2};
        TRAVERSE(gameObjects.head, GameObject, item->datum.draw()) // Draws all the 'GameObjects'.
        SDL_RenderPresent(renderer);                               // Renders everything.
        SDL_Delay(DELAY);
    }
exit: // This is a section which can be reached using 'goto' statements.
    unsetAllKeys();
    screen = SCREEN_MENU;
    return;
}

void Application::menuScreen(void)
{
    cameraPosition = {0, 0};
    constexpr int widthOfButton = 256, heightOfButton = 128;
    Button buttons[3] = {
        {{-widthOfButton / 2, heightOfButton * 2 - (double)windowHeight / 2}, {0X77, 0X77, 0X77, 0XFF}, widthOfButton, heightOfButton, "Play", [](void) -> void
         {
             screen = SCREEN_GAME;
         }},
        {{-widthOfButton / 2, heightOfButton * 4 - (double)windowHeight / 2}, {0X77, 0X77, 0X77, 0XFF}, widthOfButton, heightOfButton, "Edit", [](void) -> void
         {
             screen = SCREEN_EDIT;
         }},
        {{-widthOfButton / 2, heightOfButton * 6 - (double)windowHeight / 2}, {0X77, 0X77, 0X77, 0XFF}, widthOfButton, heightOfButton, "Quit", [](void) -> void
         {
             screen = SCREEN_EXIT;
         }}};
    SDL_Event event;
    while (screen == SCREEN_MENU)
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
                    screen = SCREEN_GAME;
                    goto exit;
                case SDL_SCANCODE_ESCAPE: // If the escape key is pressed, exit.
                    goto exit;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                for (size_t i = 0; i < sizeof(buttons) / sizeof(Button); i++)
                    buttons[i].onClick();
                break;
            }
        }
        SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0XFF);
        SDL_RenderClear(renderer);
        for (size_t i = 0; i < sizeof(buttons) / sizeof(Button); i++)
        {
            buttons[i].update(0);
            buttons[i].draw();
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(DELAY);
    }
exit:
    if (screen == SCREEN_MENU)
        screen = SCREEN_EXIT;
    return;
}

void Application::editScreen(void)
{
    gameObjects.makeEmpty();
    cameraPosition = tileMap.getCentrePositionOfTile(tileMap.getSpawnTile());
    unsigned int tileSize = tileMap.getTileSize();
    tileMap.tileOutlines = true;
    gameObjects.add({&tileMap});
    SDL_Event event;
    // Delta Time code taken from https://gamedev.stackexchange.com/questions/110825/how-to-calculate-delta-time-with-sdl.
    Uint64 now = SDL_GetPerformanceCounter(), last = 0; // Will be used to calculate 'deltaTime'.
    double deltaTime = 0;
    while (screen == SCREEN_EDIT)
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
            case SDL_MOUSEBUTTONDOWN:
            {
                int x, y;
                Uint32 button = SDL_GetMouseState(&x, &y);
                Vector2 position = {cameraPosition.x + x - windowWidth / 2, cameraPosition.y + y - windowHeight / 2};
                const TILE_TYPE *tile = tileMap.getTileAtPosition(position);
                if (tile != NULL)
                {
                    if (button == 1)
                    {
                        if (*tile < TILE_MAXIMUM_VALUE - 1)
                            tileMap.setTileAtPosition(position, (TILE_TYPE)(*tile + 1));
                        else
                            tileMap.setTileAtPosition(position, TILE_AIR);
                    }
                    else if (button == 4)
                        tileMap.setTileAtPosition(position, TILE_AIR);
                }
                break;
            }
            case SDL_QUIT: // Quit event.
                goto exit;
            }
        }
        if (isKeyDown(SDL_SCANCODE_W) || isKeyDown(SDL_SCANCODE_UP))
            cameraPosition.y -= 4 * deltaTime;
        if (isKeyDown(SDL_SCANCODE_S) || isKeyDown(SDL_SCANCODE_DOWN))
            cameraPosition.y += 4 * deltaTime;
        if (isKeyDown(SDL_SCANCODE_A) || isKeyDown(SDL_SCANCODE_LEFT))
            cameraPosition.x -= 4 * deltaTime;
        if (isKeyDown(SDL_SCANCODE_D) || isKeyDown(SDL_SCANCODE_RIGHT))
            cameraPosition.x += 4 * deltaTime;
        SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0XFF);
        SDL_RenderClear(renderer);
        TRAVERSE(gameObjects.head, GameObject, item->datum.update(deltaTime)) // Updates all the 'GameObjects'.
        TRAVERSE(gameObjects.head, GameObject, item->datum.draw())            // Draws all the 'GameObjects'.
        SDL_RenderPresent(renderer);                                          // Renders everything.
        SDL_Delay(DELAY);
    }
exit: // This is a section which can be reached using 'goto' statements.
    unsetAllKeys();
    tileMap.saveMap();
    if (screen == SCREEN_EDIT)
        screen = SCREEN_MENU;
    return;
}

void Application::run(void)
{
    while (screen != SCREEN_EXIT)
    {
        if (screen == SCREEN_MENU)
            menuScreen();
        else if (screen == SCREEN_GAME)
            gameScreen();
        else if (screen == SCREEN_EDIT)
            editScreen();
        else
        {
            puts("Unkown screen value.");
            SDL_Delay(1000);
        }
    }
}