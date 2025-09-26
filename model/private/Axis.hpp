#ifndef AXIS_HPP
#define AXIS_HPP

#include "../../shaders/Shader.hpp"

#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/matrix_transform.hpp"
#include "../../include/glm/gtc/type_ptr.hpp"

class Axis
{
    public:
        Axis ();
        ~Axis ();

        void draw (glm::mat4 Projection, glm::mat4 View);

    private:
        Shader *program;

        GLuint VAO, VBO;
        GLuint uProjectionLocation, uViewLocation;
};

#endif