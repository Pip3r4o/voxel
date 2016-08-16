#pragma once

#include <SDL2/SDL.h>

#include "GameState.h"
#include "Sprite.h"
#include "GLSLProgram.h"

class MainGame {
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

    void setWireframeMode();
    void resetWireframeMode();

    int _screenWidth;
    int _screenHeight;
    SDL_Window* _SDL;
    GameState _state;

    GLSLProgram _program;
    Sprite _sprite;
};
