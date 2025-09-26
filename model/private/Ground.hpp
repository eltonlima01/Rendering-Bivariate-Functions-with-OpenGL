#ifndef GROUND_HPP
#define GROUND_HPP

#include "../../shaders/Shader.hpp"

#include "../../include/glm/glm.hpp"
#include "../../include/glm/gtc/type_ptr.hpp"

class Ground
{
    public:
        Ground ();
        ~Ground ();

        void draw (glm::mat4 Projection, glm::mat4 View);

    private:
        Shader *program;
        
        GLuint VAO, VBO;
        GLint uProjectionLocation, uViewLocation;
};

#endif