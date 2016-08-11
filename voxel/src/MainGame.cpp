#include "MainGame.h"

MainGame::MainGame()
{
    _SDL = nullptr;
    _screenHeight = 768;
    _screenWidth = 1024;
}

MainGame::~MainGame()
{

}

void MainGame::start()
{
    initialize();
}

void MainGame::initialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    _SDL = SDL_CreateWindow("gamewindow", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
}
