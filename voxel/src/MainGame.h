#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL2/SDL.h>
#include <GL/gl.h>

#include "GameState.h"

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void start();

private:
    int _screenWidth;
    int _screenHeight;
    SDL_Window* _SDL;
    GameState _state;


    void initialize();
    void gameLoop();

};

#endif // MAINGAME_H
