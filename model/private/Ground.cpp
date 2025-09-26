#include "Ground.hpp"

Ground::Ground ()
{
    program = new Shader ("shaders/World/Ground/ground.vs", "shaders/World/Ground/ground.fs"); 
    uProjectionLocation = glGetUniformLocation (program->ID, "uProjection");
    uViewLocation = glGetUniformLocation (program->ID, "uView");
    
    glGenVertexArrays (1, &VAO);
    glBindVertexArray (VAO);

    GLfloat vertices [12] =
    {
        -100.0f, 100.0f,
        -100.0f, -100.0f,
        100.0f, 100.0f,
        100.0f, -100.0f
    };

    glGenBuffers (1, &VBO);
    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof (GLfloat), (void*)0);
    glEnableVertexAttribArray (0);

    glBindVertexArray (0);
}

Ground::~Ground ()
{
    glDeleteVertexArrays (1, &VAO);
    glDeleteBuffers (1, &VBO);

    delete program;
    program = nullptr;
}

void Ground::draw (glm::mat4 Projection, glm::mat4 View)
{
    glBindVertexArray (VAO);
    glUseProgram (program->ID);

    glUniformMatrix4fv (uProjectionLocation, 1, GL_FALSE, glm::value_ptr (Projection));
    glUniformMatrix4fv (uViewLocation, 1, GL_FALSE, glm::value_ptr (View));

    glDrawArrays (GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray (0);
    glUseProgram (0);
}