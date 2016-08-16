#pragma once

#include <GL/glew.h>

class Sprite {
public:
    void draw();

    void init(float x, float y, float width, float height);

    Sprite();
    ~Sprite();

private:
    float _width;
    float _height;
    float _x;
    float _y;

    GLuint _vboID;
    GLuint _vaoID;
};
