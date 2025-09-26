#include "Axis.hpp"
Axis::Axis ()
{
    program = new Shader ("shaders/World/Axis/axis.vs", "shaders/World/Axis/axis.fs");

    uProjectionLocation = glGetUniformLocation (program->ID, "uProjection");
    uViewLocation = glGetUniformLocation (program->ID, "uView");

    glGenVertexArrays (1, &VAO);
    glBindVertexArray (VAO);

    GLfloat vertices [] =
    {
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 100.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -100.0f, 0.02f, 0.0f, 1.0f, 0.0f, 0.0f,
        100.0f, 0.02f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.02f, -100.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.02f, 100.0f, 0.0f, 0.0f, 1.0f
    };

    glGenBuffers (1, &VBO);
    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (GLfloat), (void*)0);
    glEnableVertexAttribArray (0);

    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof (GLfloat), (void*)(3 * sizeof (GLfloat)));
    glEnableVertexAttribArray (1);

    glBindVertexArray (0);
}

Axis::~Axis ()
{
    glDeleteVertexArrays (1, &VAO);
    glDeleteBuffers (1, &VBO);

    delete program;
    program = nullptr;
}

void Axis::draw (glm::mat4 Projection, glm::mat4 View)
{
    glBindVertexArray (VAO);
    glUseProgram (program->ID);

    glUniformMatrix4fv (uProjectionLocation, 1, GL_FALSE, glm::value_ptr (Projection));
    glUniformMatrix4fv (uViewLocation, 1, GL_FALSE, glm::value_ptr (View));

    glDrawArrays (GL_LINES, 0, 6);

    glBindVertexArray (0);
    glUseProgram (0);
}