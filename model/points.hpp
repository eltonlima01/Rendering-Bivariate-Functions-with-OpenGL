#ifndef POINTS_H
#define POINTS_H

#include <vector>

#include "../shaders/Shader.hpp"
#include <GLFW/glfw3.h>

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/type_ptr.hpp"

class points
{
    public:

        static void init ();
        static void terminate ();

        static bool isAnimating;

        static void draw (glm::mat4 Projection, glm::mat4 View);
        static void setNewFunctionGraph (const std::string &newFunction);

    private:
        static Shader *program;
        
        static GLuint VAO, VBO;
        static GLint uTimeLocation,
        uProjectionLocation, uViewLocation;

        static constexpr short int N = 500;

        static float lastState;
};

#endif