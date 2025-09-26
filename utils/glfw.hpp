#ifndef GLFW_HPP
#define GLFW_HPP

#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "camera.hpp"

class glfw
{
    public:
        static GLFWwindow *window;
        static GLFWmonitor *monitor;
        static const GLFWvidmode *vidMode;

        static int windowWidth, windowHeight;

        static void init ();
        static void terminate ();

    private:
        static int wWBefore, wHBefore;
        static int windowXPos, windowYPos;

        static bool isFullscreen;

        static void cursorPosCallback (GLFWwindow *window, double xPos, double yPos);
        static void mouseButtonCallback (GLFWwindow *window, int button, int action, int mods);
        static void framebufferSizeCallback (GLFWwindow *window, GLsizei width, GLsizei height);
        static void keyCallback (GLFWwindow *window, int key, int scancode, int action, int mods);
};

#endif