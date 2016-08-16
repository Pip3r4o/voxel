#pragma once

#include <GL/glew.h>

class Sprite {
public:
    void draw();

    void initTriangle();

    void initSquare();

    Sprite();
    ~Sprite();

private:
    float _width;
    float _height;
    float _x;
    float _y;

    GLuint _eboID;
    GLuint _vboID;
    GLuint _vaoID;
};
