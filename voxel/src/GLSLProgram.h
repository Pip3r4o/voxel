#pragma once

#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
    GLSLProgram();
    ~GLSLProgram();
    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilepath);

        void linkShaders();

        void addAttribute(const std::string& attributeName);

        void use();

        void unuse();

        GLuint getProgramId();
private:
        GLuint _programID;

        GLuint _vertexShaderID;
        GLuint _fragmentShaderID;

        void compileShader(const std::string& filePath, GLuint id);
};
