#include "Sprite.h"
#include <string>
#include <iostream>

void Sprite::init(float x, float y, float width, float height)
{
    // TODO: check boundaries, check validity of params
    _x = x;
    _y = y;
    _width = width;
    _height = height;


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
    float vertices[] = {
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

    // Retrieve reference to the 'position' attribute from the vertex shader
    GLint posAttrib = 1; // set at location 1 in the .vert file //glGetAttribLocation(shaderProgram, "position");

    // Define how data is retrieved from the array
    glVertexAttribPointer(posAttrib,
                          2 /* number of components (x, y) */,
                          GL_FLOAT /* type of components */,
                          GL_FALSE /* whether to normalize values between -1.0 and 1.0 */,
                          0 /* stride - how many bytes are between each position attribute in the array */,
                          0 /* offset - how many bytes from the start of the array the attribute occurs */);

    /* ^^^
     * The function will not only store the stride and offset, but also the VBO
     * that is currently bound to GL_ARRAY_BUFFER. So we don't need to explicitly
     * bind the correct VBO when calling the actual drawing functions.
     */

    glEnableVertexAttribArray(posAttrib);

    // It is safe to unbind the VBO, as the call to VertexAttribPointer registered VBO as the currently bound
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind VAO to prevent anomalies and bugs
    glBindVertexArray(0);
}

Sprite::Sprite()
{
    _vboID = 0;
    _vaoID = 0;
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

    // will draw only the VBO, that is indirectly bound through the VAO
    glDrawArrays(GL_TRIANGLES, 0, 3 /* 3 for 3 vertices in a triangle */);

    // unbind the VAO
    glBindVertexArray(0);
}
