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

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // a VBO has not been generated yet for this sprite
    if(_vboID == 0 ) {
        // allocate a VBO memory and assign it to the ID
        glGenBuffers(1, &_vboID);
    }

    // a square consists of 2 triangles
    //    float vertexData[6 * 2];

    //    //First Triangle
    //    vertexData[0] = x + width;
    //    vertexData[1] = y + height;

    //    vertexData[2] = x;
    //    vertexData[3] = y + height;

    //    vertexData[4] = x;
    //    vertexData[5] = y;

    //    //Second Triangle
    //    vertexData[6] = x;
    //    vertexData[7] = y;

    //    vertexData[8] = x + width;
    //    vertexData[9] = y;

    //    vertexData[10] = x + width;
    //    vertexData[11] = y + height;

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

    std::string vertexShaderSource = R"(#version 330 core
            in vec2 position;

            void main()
            {
                gl_Position = vec4(position, 0.0, 1.0);
            })";
    const char* vSSC = vertexShaderSource.c_str();

    std::string fragmentShaderSource = R"(#version 330 core

                                 out vec4 outColor;

                                 void main()
                                 {
                                     outColor = vec4(1.0, 1.0, 1.0, 1.0);
                                 })";

    const char* fSSC = fragmentShaderSource.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vSSC, NULL);
    glCompileShader(vertexShader);

    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

    if(status == GL_TRUE) {
        std::cout << "VERTEX SHADER COMPILED SUCCESSFULLY!" << std::endl;

    } else {
        std::cout << "VERTEX SHADER DIDNT COMPILE!" << std::endl;
        char buffer[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, buffer);

        glDeleteShader(vertexShader); // Don't leak the shader

        std::cout << "Vertex shader compilation log: " << buffer << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fSSC, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

    if(status == GL_TRUE) {
        std::cout << "FRAGMENT SHADER COMPILED SUCCESSFULLY!" << std::endl;

    } else {
        std::cout << "FRAGMENT SHADER DIDNT COMPILE!" << std::endl;
        char buffer[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);

        glDeleteShader(fragmentShader);

        std::cout << "Fragment shader compilation log: " << buffer << std::endl;
    }

    // The two shaders are programmed to work together,
    // so we make one 'program' out of the two
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // TODO: RESEARCH: What does this do?!
    //glBindFragDataLocation(shaderProgram, 0, "outColor");

    // Link the two compiled shaders
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

    if(status == GL_TRUE) {
        std::cout << "Successfully linked the two shaders into a program!" << std::endl;

    } else {
        std::cout << "FAILED LINKING THE TWO SHADERS INTO A PROGRAM!" << std::endl;

        char buffer[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, buffer);

        std::cout << "Program Info log: " << buffer << std::endl;
    }

    // Dispose of the shaders, they've been linked already
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Every shader and rendering call will now use this program object (and the shaders)
    glUseProgram(shaderProgram);

    // Retrieve reference to the 'position' attribute from the vertex shader
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");

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

}

Sprite::Sprite()
{
    _vboID = 0;
}

Sprite::~Sprite()
{
    if(_vboID != 0) {
        glDeleteBuffers(1, &_vboID);
    }
}

void Sprite::draw()
{
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3 /* 3 for 3 vertices in a triangle */);

//    glDisableVertexAttribArray(0);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
