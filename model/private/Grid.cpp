#include "Grid.hpp"

Grid::Grid ()
{
    program = new Shader ("shaders/World/Grid/grid.vs", "shaders/World/Grid/grid.fs");

    uViewLocation = glGetUniformLocation (program->ID, "uView");
    uModelLocation = glGetUniformLocation (program->ID, "uModel");
    uProjectionLocation = glGetUniformLocation (program->ID, "uProjection");

    glGenVertexArrays (1, &VAO);
    glBindVertexArray (VAO);

    GLfloat vertices [] =
    {
        0.0f, 100.0f,
        0.0f, -100.0f
    };

    glGenBuffers (1, &VBO);
    glBindBuffer (GL_ARRAY_BUFFER, VBO);
    glBufferData (GL_ARRAY_BUFFER, sizeof (vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof (GLfloat), (void*)0);
    glEnableVertexAttribArray (0);
    glBindVertexArray (0);
}

Grid::~Grid ()
{
    glDeleteVertexArrays (1, &VAO);
    glDeleteBuffers (1, &VBO);

    delete program;
    program = nullptr;
}

void Grid::draw (glm::mat4 Projection, glm::mat4 View)
{
    glBindVertexArray (VAO);
    glUseProgram (program->ID);

    glUniformMatrix4fv (uProjectionLocation, 1, GL_FALSE, glm::value_ptr (Projection));
    glUniformMatrix4fv (uViewLocation, 1, GL_FALSE, glm::value_ptr (View));

    for (char i = -100; i <= 100; i++)
    {
        glm::mat4 Model = glm::mat4 (1.0f);
        Model = glm::translate (Model, glm::vec3 (static_cast<float>(i), 0.0f, 0.0f));

        glUniformMatrix4fv (uModelLocation, 1, GL_FALSE, glm::value_ptr (Model));

        glDrawArrays (GL_LINES, 0, 2);

        Model = glm::translate (Model, glm::vec3 (0.0f, 0.0f, static_cast<float>(i)));
        Model = glm::rotate (Model, 1.57079637050628662f, glm::vec3 (0.0f, 1.0f, 0.0f));

        glUniformMatrix4fv (uModelLocation, 1, GL_FALSE, glm::value_ptr (Model));

        glDrawArrays (GL_LINES, 0, 2);
    }
    
    glBindVertexArray (0);
    glUseProgram (0);
}