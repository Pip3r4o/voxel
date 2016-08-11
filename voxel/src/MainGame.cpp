#include "MainGame.h"
#include "GameState.h"

MainGame::MainGame()
{
    _SDL = nullptr;
    _screenHeight = 768;
    _screenWidth = 1024;
    _state = GameState::STOPPED;
}

MainGame::~MainGame() {}

void MainGame::start()
{
    initialize();

    _state = GameState::PLAYING;

    gameLoop();
}

void MainGame::initialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    _SDL = SDL_CreateWindow("gamewindow", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight,
                            SDL_WINDOW_OPENGL);
}

void MainGame::gameLoop()
{
    SDL_Event currEvent;

    while (_state == GameState::PLAYING) {
        while (SDL_PollEvent(&currEvent)) {
            switch (currEvent.type) {
                case SDL_MOUSEMOTION:
                    printf("Moved mouse to X:%d Y:%d\n\n", currEvent.motion.x,
                           currEvent.motion.y);
                    break;

                default:
                    printf("Unhandled event ...\n");
                    break;
            }
        }
    }
}
