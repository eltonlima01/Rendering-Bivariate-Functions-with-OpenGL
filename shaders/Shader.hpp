#ifndef SHADER_H
#define SHADER_H

#include "../include/glad/glad.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader
{
    public:
        Shader (const char *vertexPath, const char *fragmentPath);
        ~Shader ();

        GLuint ID;

    private:
        void checkCompileErrors (GLuint shader, std::string type);
};

#endif