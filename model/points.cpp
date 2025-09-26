#include "points.hpp"

// ========== VARIABLES ========== //

Shader* points::program = nullptr;

GLuint points::VAO = 0, points::VBO = 0;

GLint points::uTimeLocation = 0,
points::uProjectionLocation = 0, points::uViewLocation = 0;

float points::lastState = 0.0f;

bool points::isAnimating = true;

// ========== MAIN METHODS ========== //

void points::init ()
{
    program = new Shader ("shaders/Points/points.vs", "shaders/Points/points.fs");

    uTimeLocation = glGetUniformLocation (program->ID, "uTime");
    uViewLocation = glGetUniformLocation (program->ID, "uView");
    uProjectionLocation = glGetUniformLocation (program->ID, "uProjection");
    
    std::vector<GLfloat> vertices;

    float R = 2.5f;

    for (short i = 0; i <= N; i++)
    {
        for (short j = 0; j <= N; j++)
        {
            float x = -R + 2.0f * R * static_cast<float>(i) / static_cast<float>(N);
            float z = -R + 2.0f * R * static_cast<float>(j) / static_cast<float>(N);
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

    setNewFunctionGraph ("(x * z * ((x * x) - (z * z))) / ((x * x) + (z * z))");
}

void points::terminate ()
{
    glDeleteVertexArrays (1, &VAO);
    glDeleteBuffers (1, &VBO);

    delete program;
    program = nullptr;
}

// ========== METHODS ========== //

void points::draw (glm::mat4 Projection, glm::mat4 View)
{
    glBindVertexArray (VAO);
    glUseProgram (program->ID);

    glUniformMatrix4fv (uViewLocation, 1, GL_FALSE, glm::value_ptr (View));
    glUniformMatrix4fv (uProjectionLocation, 1, GL_FALSE, glm::value_ptr (Projection));

    if (isAnimating)
    {
        lastState = static_cast<float>(glfwGetTime ());
    }

    glUniform1f (uTimeLocation, lastState);

    glDrawArrays (GL_POINTS, 0, (N + 1) * (N + 1));

    glBindVertexArray (0);
    glUseProgram (0);
}

void points::setNewFunctionGraph (const std::string &newFunction)
{
    std::ofstream file ("shaders/Points/points.vs");

    file <<
    "#version 330 core\n\n"
    "layout (location = 0) in vec2 vPos;\n"
    "out float height;\n\n"
    "uniform mat4 uProjection, uView;\n"
    "uniform float uTime;\n\n"
    "void main ()\n{\n"
    "float e = 2.71828f;\n"
    "float pi = 3.14159;\n\n"
    "float x = vPos.x;\n"
    "float z = vPos.y;\n"
    "float y = sin (uTime) * (" + newFunction + ");\n\n"
    "height = y;\n"
    "gl_Position = uProjection * uView * vec4 (x, y, z, 1.0f);\n}";

    file.close ();

    delete program;
    program = new Shader ("shaders/Points/points.vs", "shaders/Points/points.fs");

    uTimeLocation = glGetUniformLocation (program->ID, "uTime");
    uViewLocation = glGetUniformLocation (program->ID, "uView");
    uProjectionLocation = glGetUniformLocation (program->ID, "uProjection");
}