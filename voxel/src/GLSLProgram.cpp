#include "GLSLProgram.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include "SDL2/SDL.h"

GLSLProgram::GLSLProgram()
    : _programID(0), _vertexShaderID(0), _fragmentShaderID(0)
{

}

GLSLProgram::~GLSLProgram()
{
    if(_programID != 0) {
        glDeleteProgram(_programID);
    }
}

void GLSLProgram::use()
{
    glUseProgram(_programID);

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

    GLint timeValue = SDL_GetTicks() / 100;
    GLfloat greenValue = (sin(timeValue) / 2) + 0.05;
    GLfloat blueValue = (sin(timeValue) / 2) + 0.3;
    GLint vertexColorLocation = glGetUniformLocation(getProgramId(), "rainbowColor");

    glUniform4f(vertexColorLocation, 0.30f, greenValue, blueValue, 1.0f);

}

void GLSLProgram::unuse()
{
    glUseProgram(0);

    GLint posAttrib = 1;
    glDisableVertexAttribArray(posAttrib);
}

void GLSLProgram::linkShaders()
{
    // The two shaders are programmed to work together,
    // so we make one 'program' out of the two
    _programID = glCreateProgram();
    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);

    // Link the two compiled shaders
    glLinkProgram(_programID);

    GLint status;
    glGetProgramiv(_programID, GL_LINK_STATUS, &status);

    if(status == GL_FALSE) {
        std::cout << "FAILED LINKING THE TWO SHADERS INTO A PROGRAM!" << std::endl;

        char buffer[512];
        glGetProgramInfoLog(_programID, 512, NULL, buffer);

        std::cout << "Program Info log: " << buffer << std::endl;

        glDeleteProgram(_programID);
        glDeleteShader(_vertexShaderID);
        glDeleteShader(_fragmentShaderID);
    }

    // Dispose of the shaders, they've been linked already
    glDetachShader(_programID, _vertexShaderID);
    glDetachShader(_programID, _fragmentShaderID);
    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath)
{
    _vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    _fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    compileShader(vertexShaderFilePath, _vertexShaderID);
    compileShader(fragmentShaderFilepath, _fragmentShaderID);
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint shaderId)
{
    // Open the file
    std::ifstream shaderFile(filePath);

    if (shaderFile.fail()) {
        perror(filePath.c_str());

        std::cout << "FAILED TO OPEN SHADER: " << filePath << std::endl;
    }

    // File contents stores all the text in the file
    std::string fileContents = "";
    std::string line;

    // Get all the lines in the file and add it to the contents
    while (std::getline(shaderFile, line)) {
        fileContents += line + "\n";
    }

    shaderFile.close();

    const char* shaderSource = fileContents.c_str();

    glShaderSource(shaderId, 1, &shaderSource, NULL);
    glCompileShader(shaderId);

    GLint status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);

    if(status == GL_FALSE) {
        std::cout << "SHADER DIDNT COMPILE!" << std::endl;
        char buffer[512];
        glGetShaderInfoLog(shaderId, 512, NULL, buffer);

        glDeleteShader(shaderId); // Don't leak the shader

        std::cout << "Shader compilation log: " << buffer << std::endl;
    }
}


GLuint GLSLProgram::getProgramId()
{
    return _programID;
}
