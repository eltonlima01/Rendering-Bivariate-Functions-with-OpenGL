#include "Shader.hpp"

Shader::Shader (const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode, fragmentCode;
    std::ifstream vShaderFile, fShaderFile;

    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try
    {
    vShaderFile.open (vertexPath);
    fShaderFile.open (fragmentPath);

    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf ();
    fShaderStream << fShaderFile.rdbuf ();

    vShaderFile.close ();
    fShaderFile.close ();

    vertexCode = vShaderStream.str ();
    fragmentCode = fShaderStream.str ();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << e.what () << std::endl;
    }

    const char *vShaderCode = vertexCode.c_str (),
    *fShaderCode = fragmentCode.c_str ();

    GLuint vertex = glCreateShader (GL_VERTEX_SHADER),
    fragment = glCreateShader (GL_FRAGMENT_SHADER);

    glShaderSource (vertex, 1, &vShaderCode, NULL);
    glCompileShader (vertex);
    checkCompileErrors (vertex, "GL_VERTEX_SHADER");

    glShaderSource (fragment, 1, &fShaderCode, NULL);
    glCompileShader (fragment);
    checkCompileErrors (fragment, "GL_FRAGMENT_SHADER");

    ID = glCreateProgram ();

    glAttachShader (ID, vertex);
    glAttachShader (ID, fragment);
    glLinkProgram (ID);
    checkCompileErrors (ID, "GL_PROGRAM");

    glDeleteShader (vertex);
    glDeleteShader (fragment);
}

Shader::~Shader ()
{
    glDeleteProgram (ID);
}

void Shader::checkCompileErrors (GLuint shader, std::string type)
{
    GLint params;
    GLchar infoLog [1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv (shader, GL_COMPILE_STATUS, &params);

        if (!params)
        {
            glGetShaderInfoLog (shader, 1024, NULL, infoLog);

            std::cout << "ERROR::" << type << "\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv (shader, GL_LINK_STATUS, &params);

        if (!params)
        {
            glGetProgramInfoLog (shader, 1024, NULL, infoLog);

            std::cout << "ERROR::" << type << "\n" << infoLog << std::endl;
        }
    }
}