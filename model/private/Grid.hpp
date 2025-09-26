#ifndef GRID_HPP
#define GRID_HPP

#include "../../shaders/Shader.hpp"

#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/matrix_transform.hpp"
#include "../../include/glm/gtc/type_ptr.hpp"

class Grid
{
    public:
        Grid ();
        ~Grid ();

        void draw (glm::mat4 Projection, glm::mat4 View);

    private:
        Shader *program;

        GLuint VAO, VBO;
        GLint uProjectionLocation, uViewLocation, uModelLocation;
};

#endif