#ifndef MAINGAME_H
#define MAINGAME_H

#include <SDL2/SDL.h>
#include <GL/gl.h>

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void start();
    void initialize();

private:
    int _screenWidth;
    int _screenHeight;
    SDL_Window* _SDL;
};

#endif // MAINGAME_H
