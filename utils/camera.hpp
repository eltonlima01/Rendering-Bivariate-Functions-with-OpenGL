#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

class camera
{
    public:
        static bool cameraMode;

        static float lastX, lastY;

        static void setCursorPos (float xOffset, float yOffset);

        static void setViewMatrix ();
        static glm::mat4 getViewMatrix ();

        static void setProjectionMatrix (float width, float height);
        static glm::mat4 getProjectionMatrix ();

    private:
        static glm::vec3 position;
        static glm::mat4 viewMatrix, projectionMatrix;

        static float angleYaw, anglePitch;

        static constexpr float sensitivity = 0.1f;
        static constexpr float radius = 10.0f;

        static void setCameraVectors ();
};

#endif