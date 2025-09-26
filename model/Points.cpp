#include "Points.hpp"

Points::Points ()
{
    program = new Shader ("shaders/Points/points.vs", "shaders/Points/points.fs");

    uProjectionLocation = glGetUniformLocation (program->ID, "uProjection");
    uViewLocation = glGetUniformLocation (program->ID, "uView");
    uModelLocation = glGetUniformLocation (program->ID, "uModel");
    uTimeLocation = glGetUniformLocation (program->ID, "uTime");
    
    std::vector<GLfloat> vertices;

    float R = 3.0f;

    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= N; j++)
        {
            float x = -R + 2.0f * R * i / N;
            float z = -R + 2.0f * R * j / N;
            vertices.push_back(x);
            vertices.push_back(z);
        }
    }

    glGenVertexArrays (1, &VAO);
    glBindVertexArray (VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
}

Points::~Points ()
{
    glDeleteVertexArrays (1, &VAO);
    glDeleteBuffers (1, &VBO);

    delete program;
    program = nullptr;
}

void Points::draw (glm::mat4 Projection, glm::mat4 View)
{
    glBindVertexArray (VAO);
    glUseProgram (program->ID);

    glm::mat4 Model (1.0f);

    glUniformMatrix4fv (uViewLocation, 1, GL_FALSE, glm::value_ptr (View));
    glUniformMatrix4fv (uModelLocation, 1, GL_FALSE, glm::value_ptr (Model));
    glUniformMatrix4fv (uProjectionLocation, 1, GL_FALSE, glm::value_ptr (Projection));

    glUniform1f (uTimeLocation, static_cast<float>(glfwGetTime ()));

    glDrawArrays (GL_POINTS, 0, (N + 1) * (N + 1));

    glBindVertexArray (0);
    glUseProgram (0);
}