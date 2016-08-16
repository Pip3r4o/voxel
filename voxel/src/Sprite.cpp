#include "Sprite.h"
#include <string>
#include <iostream>

void Sprite::initTriangle()
{
    /*
     * Vertex Array Objects (VAO)s store all of the links between the attributes and your VBOs with raw vertex data
     * Every time we call glVertexAttribPointer, that information will be stored in that VAO.
     * This makes switching between different vertex data and vertex formats as easy as binding a different VAO
     */

    glGenVertexArrays(1, &_vaoID);
    glBindVertexArray(_vaoID);

    // a VBO has not been generated yet for this sprite
    if(_vboID == 0 ) {
        // allocate a VBO memory and assign it to the ID
        glGenBuffers(1, &_vboID);
    }

    // TODO: currently hardcoded to draw a triangle
    GLfloat vertices[] = {
        0.0f,  0.5f, // Vertex 1 (X, Y)
        0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f  // Vertex 3 (X, Y)
    };

    // Makes our VBO the active GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    // Uploads the bound GL_ARRAY_BUFFER to the graphics card
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                 GL_STATIC_DRAW /*
             * GL_STATIC_DRAW - the data will most likely not change at all or very rarely
             * GL_DYNAMIC_DRAW -the data is likely to change a lot
             * GL_STREAM_DRAW - the data will change every time it is drawn */);
}

void Sprite::initSquare()
{
    /*
     * Vertex Array Objects (VAO)s store all of the links between the attributes and your VBOs with raw vertex data
     * Every time we call glVertexAttribPointer, that information will be stored in that VAO.
     * This makes switching between different vertex data and vertex formats as easy as binding a different VAO
     */

    glGenVertexArrays(1, &_vaoID);
    glBindVertexArray(_vaoID);

    if(_vboID == 0 ) {
        glGenBuffers(1, &_vboID);
    }

    if(_eboID == 0 ) {
        glGenBuffers(1, &_eboID);
    }

    // TODO: currently hardcoded to draw a square
    GLfloat vertices[] = {
        0.5f,  0.5f,  // Top Right
        0.5f, -0.5f,  // Bottom Right
        -0.5f, -0.5f,  // Bottom Left
        -0.5f,  0.5f,  // Top Left
    };

    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3,   // First Triangle
        1, 2, 3    // Second Triangle
    };

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);

    // Uploads the bound GL_ARRAY_BUFFER to the graphics card
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                 GL_STATIC_DRAW /*
             * GL_STATIC_DRAW - the data will most likely not change at all or very rarely
             * GL_DYNAMIC_DRAW -the data is likely to change a lot
             * GL_STREAM_DRAW - the data will change every time it is drawn */);

    // Makes our EBO the active GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _eboID);

    // Uploads the bound GL_ELEMENT_ARRAY_BUFFER to the graphics card
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW /*
             * GL_STATIC_DRAW - the data will most likely not change at all or very rarely
             * GL_DYNAMIC_DRAW -the data is likely to change a lot
             * GL_STREAM_DRAW - the data will change every time it is drawn */);
}

Sprite::Sprite() : _vboID(0), _vaoID(0), _eboID(0)
{
}

Sprite::~Sprite()
{
    if(_vboID != 0) {
        glDeleteBuffers(1, &_vboID);
    }

    if(_vaoID != 0) {
        glDeleteVertexArrays(1, &_vaoID);
    }
}

void Sprite::draw()
{
    // bind our VAO - contains all the information about our sprite
    glBindVertexArray(_vaoID);

    if(_eboID != 0) {

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    } else if(_vboID != 0) {
        // will draw only the VBO, that is indirectly bound through the VAO
        glDrawArrays(GL_TRIANGLES, 0, 3 /* 3 for 3 vertices in a triangle */);
    }

    // unbind the VAO
    glBindVertexArray(0);
}
