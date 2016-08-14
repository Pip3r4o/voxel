#include <GL/glew.h>

#include "MainGame.h"
#include "GameState.h"
#include <exception>
#include <iostream>


MainGame::MainGame()
{
    _SDL = nullptr;
    _screenHeight = 768;
    _screenWidth = 1024;
    _state = GameState::STOPPED;
}

MainGame::~MainGame() {}

void MainGame::run()
{
    initialize();

    _state = GameState::PLAYING;

    _sprite.init(0.0f, 0.0f, 1.0f, 1.0f);

    gameLoop();

    SDL_Quit();
}

void MainGame::initialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    // TODO: RESEARCH: What do these do?!
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Will create 2 screens to draw and clean on
    // scrA and scrB
    // initially we draw on scrA
    // next frame we switch to scrB
    // and draw on scrB while scrA is cleaned
    // then the two are switched
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    _SDL = SDL_CreateWindow("gamewindow", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight,
                            SDL_WINDOW_OPENGL);

    if(_SDL == nullptr) {
        std::cout << "SDL NOT INITIALIZED! TERMINATING PROGRAM" << std::endl;
        throw;
    }

    setupGL();
}

void MainGame::setupGL()
{
    SDL_GLContext context = SDL_GL_CreateContext(_SDL);

    if(context == nullptr) {
        std::cout << "COULDN'T INITIALIZE SDL_GLContext! TERMINATING PROGRAM" << std::endl;
        throw;
    }

    glewExperimental = GL_TRUE;

    GLenum err = glewInit();

    if(err != GLEW_NO_ERROR) {
        std::cout << "GLEW COULDN'T INITIALIZE! TERMINATING PROGRAM" << std::endl;
        throw;
    }

    // Sets the initial color that will be drawn
    // every time the window is cleared
    glClearColor(0.2f, 0.6f, 0.65f, 0.5f);

    auto glslVer = glGetString(GL_SHADING_LANGUAGE_VERSION);
    auto glVer = glGetString(GL_VERSION);

    // outputs version supported by the graphics driver
    std::cout << "OpenGL Version (supported by the Graphics Driver): " << glVer << std::endl;
    std::cout << "GL Shading Language Version: " << glslVer << std::endl;
}

void MainGame::gameLoop()
{
    while (_state == GameState::PLAYING) {
        draw();
        handleInput();
    }
}

void MainGame::handleInput()
{
    SDL_Event currEvent;

    while (SDL_PollEvent(&currEvent)) {
        switch (currEvent.type) {
            case SDL_MOUSEMOTION:
                // printf("Moved mouse to X:%d Y:%d\n\n", currEvent.motion.x,
                // currEvent.motion.y);
                break;

            case SDL_MOUSEBUTTONUP:
                _state = GameState::STOPPED;
                break;

            case SDL_QUIT:
                _state = GameState::STOPPED;
                break;

            default:
                // printf("Unhandled event ...\n");
                break;
        }
    }
}

void MainGame::draw()
{
    // TODO: RESEARCH: What does this do?!
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _sprite.draw();

    /// Will swap the 2 screens that we draw on and clear
    /// scrA and scrB
    /// initially we draw on scrA
    /// next frame we switch to scrB
    /// and draw on scrB while scrA is cleaned
    /// then the two are switched back
    SDL_GL_SwapWindow(_SDL);
}
