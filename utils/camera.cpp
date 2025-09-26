#include "camera.hpp"

// ========== VARIABLES ========== //

float camera::lastX = 0.0f, camera::lastY = 0.0f;
float camera::angleYaw = 35.0f, camera::anglePitch = 35.0f;

glm::vec3 camera::position = glm::vec3
(
    position.x = radius * cos (glm::radians (angleYaw)) * cos (glm::radians (anglePitch)),
    position.y = radius * sin (glm::radians (anglePitch)),
    position.z = radius * sin (glm::radians (angleYaw)) * cos (glm::radians (anglePitch))
);

glm::mat4 camera::projectionMatrix = glm::mat4 (1.0f);
glm::mat4 camera::viewMatrix = glm::lookAt
(
    position,
    glm::vec3 (0.0f),
    glm::vec3 (0.0f, 1.0f, 0.0f)
);

bool camera::cameraMode = false;

// ========== METHODS ========== //

void camera::setCursorPos (float xOffset, float yOffset)
{
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    angleYaw += xOffset;
    anglePitch += yOffset;

    if (anglePitch > 89.0f)
    {
        anglePitch = 89.0f;
    }

    if (anglePitch < 1.0f)
    {
        anglePitch = 1.0f;
    }

    setCameraVectors ();
}

void camera::setCameraVectors ()
{
    position.x = radius * cos (glm::radians (angleYaw)) * cos (glm::radians (anglePitch));
    position.y = radius * sin (glm::radians (anglePitch));
    position.z = radius * sin (glm::radians (angleYaw)) * cos (glm::radians (anglePitch));

    setViewMatrix ();
}

// ========== GETTERS AND SETTERS ========== //

void camera::setViewMatrix ()
{
    viewMatrix = glm::lookAt
    (
        position,
        glm::vec3 (0.0f),
        glm::vec3 (0.0f, 1.0f, 0.0f)
    );
}

glm::mat4 camera::getViewMatrix ()
{
    return viewMatrix;
}

void camera::setProjectionMatrix (float width, float height)
{
    projectionMatrix = glm::perspective
    (
        0.785398185253143311f,
        width / height,
        0.1f, 100.0f
    );
}

glm::mat4 camera::getProjectionMatrix ()
{
    return projectionMatrix;
}