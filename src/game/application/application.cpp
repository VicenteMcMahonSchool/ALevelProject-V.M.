#include "./application.hpp"

// Constructor for application, this is used to make the class.
Application::Application()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        throw std::runtime_error(SDL_GetError());
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;
    // Finds game controller.
    for (int i = 0; i < SDL_NumJoysticks(); i++)
    {
        if (SDL_IsGameController(i))
        {
            controller = SDL_GameControllerOpen(i);
            break;
        }
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    TileMap &tileMap = gameObjects.add(TILE_MAP, true)->tileMap;
    new (&tileMap) TileMap{{0, 0}, 120}; // Using placement new to prevent calling the destructor.
}

// Destructor for application, this is used to free memory.
Application::~Application()
{
    SDL_GameControllerClose(controller);
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
    timePassed = numberOfTicks = 0; // Sets both of them to 0.
    Player &player = gameObjects.add(PLAYER)->player;
    TileMap &tileMap = gameObjects.getGameObjectOfType(TILE_MAP)->tileMap;
    new (&player) Player{{0, 0}}; // Using placement new to prevent calling the destructor.
    tileMap.resetRemovedCoins();
    unsigned int tileSize = tileMap.getTileSize();
    player = Player{tileMap.getCentrePositionOfTile(tileMap.getSpawnTile()) - (Vector2){(double)tileSize / 2, (double)tileSize / 2} /* (Vector2){(double)tileSize / 2, (double)tileSize / 2} */};
    tileMap.tileOutlines = false;
    SDL_Event event;
    // Delta Time code taken from https://gamedev.stackexchange.com/questions/110825/how-to-calculate-delta-time-with-sdl.
    Uint64 now = SDL_GetPerformanceCounter(), last = 0; // Will be used to calculate 'deltaTime'.
    double deltaTime = 0;
    while (screen == SCREEN_GAME_NORMAL || screen == SCREEN_GAME_TIME_SCALE)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        switch (screen)
        {

        case SCREEN_GAME_TIME_SCALE:
            deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency()) * timeScale;
            break;
        case SCREEN_GAME_NORMAL:
            deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
            break;
        }
        timePassed += deltaTime;
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
            case SDL_CONTROLLERBUTTONDOWN:
                if (controller != NULL && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller)))
                    switch (event.cbutton.button)
                    {
                    case SDL_CONTROLLER_BUTTON_START:
                        goto exit;
                    default:
                        setButtonDown(event.cbutton.button);
                    }
                break;
            case SDL_CONTROLLERBUTTONUP:
                if (controller != NULL && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller)))
                    unsetButtonDown(event.cbutton.button);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE: // If the escape key is pressed, exit.
                    goto exit;
                default:
                    setButtonDown(event.key.keysym.scancode);
                    break;
                }
                break;
            case SDL_KEYUP:
                unsetButtonDown(event.key.keysym.scancode);
                break;
            }
        }
        SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0XFF);
        SDL_RenderClear(renderer); // Clears the screen.
        while (timePassed > 1000)
        {
            timePassed -= 1000;
            numberOfTicks++;
            gameObjects.tick();
        }
        gameObjects.update(deltaTime);
        cameraPosition = player.getPosition() + (Vector2){(double)player.getRectangle().w / 2, (double)player.getRectangle().h / 2};
        gameObjects.drawShadows();
        gameObjects.draw();
        if (screen != SCREEN_GAME_NORMAL && screen != SCREEN_GAME_TIME_SCALE)
            break;
        SDL_RenderPresent(renderer); // Renders everything.
        SDL_Delay(DELAY);
    }
exit: // This is a section which can be reached using 'goto' statements.
    unsetAllButtons();
    gameObjects.makeEmpty();
    if (screen == SCREEN_GAME_NORMAL || screen == SCREEN_GAME_TIME_SCALE)
        screen = SCREEN_MENU;
    return;
}

void Application::menuScreen(void)
{
    cameraPosition = {0, 0};
    int widthOfButton = (256 * windowWidth) / 1920, heightOfButton = (108 * windowHeight) / 1080;
    size_t selectedButton = 0;
    Button buttons[4] = {
        {{-(double)widthOfButton / 2, heightOfButton * 2 - (double)windowHeight / 2}, {0X77, 0X77, 0X77, 0XFF}, widthOfButton, heightOfButton, "Play", [](void) -> void
         {
             screen = SCREEN_GAME_NORMAL;
         }},
        {{-(double)widthOfButton / 2, heightOfButton * 4 - (double)windowHeight / 2}, {0X77, 0X77, 0X77, 0XFF}, widthOfButton, heightOfButton, "Challenge", [](void) -> void
         {
             screen = SCREEN_GAME_TIME_SCALE;
         }},
        {{-(double)widthOfButton / 2, heightOfButton * 6 - (double)windowHeight / 2}, {0X77, 0X77, 0X77, 0XFF}, widthOfButton, heightOfButton, "Edit", [](void) -> void
         {
             screen = SCREEN_EDIT;
         }},
        {{-(double)widthOfButton / 2, heightOfButton * 8 - (double)windowHeight / 2}, {0X77, 0X77, 0X77, 0XFF}, widthOfButton, heightOfButton, "Quit", [](void) -> void
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
            case SDL_CONTROLLERBUTTONDOWN:
                if (controller != NULL && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller)))
                    switch (event.cbutton.button)
                    {
                    case SDL_CONTROLLER_BUTTON_START:
                        goto exit;
                    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                        selectedButton = (selectedButton + 1) % (sizeof(buttons) / sizeof(decltype(*buttons)));
                        break;
                    case SDL_CONTROLLER_BUTTON_DPAD_UP:
                        selectedButton = (selectedButton - 1) % (sizeof(buttons) / sizeof(decltype(*buttons)));
                        break;
                    case SDL_CONTROLLER_BUTTON_A:
                        buttons[selectedButton].onAction(false);
                        break;
                    default:
                        setButtonDown(event.cbutton.button);
                    }
                break;
            case SDL_CONTROLLERBUTTONUP:
                if (controller != NULL && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller)))
                    unsetButtonDown(event.cbutton.button);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE: // If the escape key is pressed, exit.
                    goto exit;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                for (size_t i = 0; i < sizeof(buttons) / sizeof(decltype(*buttons)); i++)
                    buttons[i].onAction(true);
                break;
            }
        }
        SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0XFF);
        SDL_RenderClear(renderer);
        for (size_t i = 0; i < sizeof(buttons) / sizeof(decltype(*buttons)); i++)
        {
            buttons[i].update(0);
            buttons[i].draw();
            if (i == selectedButton)
            {
                SDL_Rect rectangle = buttons[i].getRectangle();
                rectangle.x -= 6;
                rectangle.y -= 6;
                rectangle.w += 12;
                rectangle.h += 12;
                SDL_RenderDrawRect(renderer, &rectangle);
            }
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
    size_t cursorSize = 1;
    TileMap &tileMap = gameObjects.getGameObjectOfType(TILE_MAP)->tileMap;
    tileMap.resetRemovedCoins();
    cameraPosition = tileMap.getCentrePositionOfTile(tileMap.getSpawnTile());
    unsigned int tileSize = tileMap.getTileSize();
    tileMap.tileOutlines = true;
    SDL_Event event;
    // Delta Time code taken from https://gamedev.stackexchange.com/questions/110825/how-to-calculate-delta-time-with-sdl.
    Uint64 now = SDL_GetPerformanceCounter(), last = 0; // Will be used to calculate 'deltaTime'.
    double deltaTime = 0;
    while (screen == SCREEN_EDIT)
    {
        last = now;
        now = SDL_GetPerformanceCounter();
        deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());
        timePassed += deltaTime;
        /*
        Loops until there is an error getting the event. The 'event' variable is passed by reference to 'SDL_PollEvent',
        this function will get the current event and store it in 'event'.
        */
        while (SDL_PollEvent(&event) > 0)
        {
            switch (event.type)
            {
            case SDL_CONTROLLERBUTTONDOWN:
                if (controller != NULL && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller)))
                    switch (event.cbutton.button)
                    {
                    case SDL_CONTROLLER_BUTTON_START:
                        goto exit;
                    case SDL_CONTROLLER_BUTTON_A:
                    {
                        const TILE_TYPE *tile = tileMap.getTileAtPosition(cameraPosition);
                        if (tile != NULL && *tile < TILE_NORMAL_MAXIMUM_VALUE - 1)
                            tileMap.setTilesAroundPosition(cameraPosition, (TILE_TYPE)(*tile + 1), cursorSize);
                        else
                            tileMap.setTilesAroundPosition(cameraPosition, TILE_AIR, cursorSize);
                        break;
                    }
                    case SDL_CONTROLLER_BUTTON_B:
                    {
                        const TILE_TYPE *tile = tileMap.getTileAtPosition(cameraPosition);
                        tileMap.setTilesAroundPosition(cameraPosition, TILE_AIR, cursorSize);
                        break;
                    }
                    case SDL_CONTROLLER_BUTTON_X:
                        cursorSize += 2;
                        break;
                    case SDL_CONTROLLER_BUTTON_Y:
                        if (cursorSize > 1)
                            cursorSize -= 2;
                        break;
                    default:
                        setButtonDown(event.cbutton.button);
                    }
                break;
            case SDL_CONTROLLERBUTTONUP:
                if (controller != NULL && event.cdevice.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller)))
                    unsetButtonDown(event.cbutton.button);
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_ESCAPE: // If the escape key is pressed, exit.
                    goto exit;
                default:
                    setButtonDown(event.key.keysym.scancode);
                    break;
                }
                break;
            case SDL_KEYUP:
                unsetButtonDown(event.key.keysym.scancode);
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
                        if (*tile < TILE_NORMAL_MAXIMUM_VALUE - 1)
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
        if (isButtonDown(SDL_SCANCODE_W) || isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_UP))
            cameraPosition.y -= 1 * deltaTime;
        if (isButtonDown(SDL_SCANCODE_S) || isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN))
            cameraPosition.y += 1 * deltaTime;
        if (isButtonDown(SDL_SCANCODE_A) || isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT))
            cameraPosition.x -= 1 * deltaTime;
        if (isButtonDown(SDL_SCANCODE_D) || isButtonDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
            cameraPosition.x += 1 * deltaTime;

        SDL_SetRenderDrawColour(renderer, 0X33, 0X33, 0X33, 0XFF);
        SDL_RenderClear(renderer);
        while (timePassed > 1000)
        {
            timePassed -= 1000;
            numberOfTicks++;
            gameObjects.tick();
        }
        gameObjects.update(deltaTime);
        gameObjects.drawShadows();
        gameObjects.draw();
        if (controller != NULL)
        {
            const TILE_TYPE *tile = tileMap.getTileAtPosition(cameraPosition);
            if (tile != NULL)
            {
                SDL_SetRenderDrawColour(renderer, 0XAA, 0XAA, 0XAA, 0XFF);
                Vector2 centrePosition = tileMap.getCentrePositionOfTile(tile);
                SDL_Rect rectangle = {(int)(centrePosition.x - (double)tileSize / 2 - cursorSize / 2 * tileSize + (double)windowWidth / 2 - cameraPosition.x), (int)(centrePosition.y - (double)tileSize / 2 - cursorSize / 2 * tileSize + (double)windowHeight / 2 - cameraPosition.y), (int)tileSize * (int)cursorSize, (int)tileSize * (int)cursorSize};
                SDL_RenderDrawRect(renderer, &rectangle);
            }
        }
        SDL_RenderPresent(renderer); // Renders everything.
        SDL_Delay(DELAY);
    }
exit: // This is a section which can be reached using 'goto' statements.
    unsetAllButtons();
    tileMap.saveMap();
    gameObjects.makeEmpty();
    if (screen == SCREEN_EDIT)
        screen = SCREEN_MENU;
    return;
}

void Application::winScreen(void)
{
    SDL_SetRenderDrawColour(renderer, 0X00, 0XFF, 0X00, 0X55);
    SDL_Rect rectangle{0, 0, windowWidth, windowHeight};
    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    screen = SCREEN_MENU;
}
void Application::loseScreen(void)
{
    SDL_SetRenderDrawColour(renderer, 0XFF, 0X00, 0X00, 0X55);
    SDL_Rect rectangle{0, 0, windowWidth, windowHeight};
    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderPresent(renderer);
    SDL_Delay(1000);
    screen = SCREEN_MENU;
}

void Application::run(void)
{
    while (screen != SCREEN_EXIT)
    {
        if (screen == SCREEN_MENU)
            menuScreen();
        else if (screen == SCREEN_GAME_NORMAL || screen == SCREEN_GAME_TIME_SCALE)
            gameScreen();
        else if (screen == SCREEN_EDIT)
            editScreen();
        else if (screen == SCREEN_WIN)
            winScreen();
        else if (screen == SCREEN_LOSE)
            loseScreen();
        else
        {
            puts("Unkown screen value.");
            SDL_Delay(1000);
        }
    }
}