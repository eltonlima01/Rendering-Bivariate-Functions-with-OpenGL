#ifndef POINTS_H
#define POINTS_H

#include <vector>

#include "../shaders/Shader.hpp"
#include "../include/GLFW/glfw3.h"

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

class Points
{
    public:
        Points ();
        ~Points ();

        void draw (glm::mat4 Projection, glm::mat4 View);

    private:
        Shader *program;
        
        GLuint VAO, VBO;
        GLint uProjectionLocation, uViewLocation,
        uModelLocation, uTimeLocation;

        int N = 200;
};

#endif