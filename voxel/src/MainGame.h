#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL2/SDL.h>

#include "GameState.h"
#include "Sprite.h"

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initialize();
    void setupGL();

    void gameLoop();
    void handleInput();
    void draw();

    int _screenWidth;
    int _screenHeight;
    SDL_Window* _SDL;
    GameState _state;

    Sprite _sprite;
};

#endif // MAINGAME_H
