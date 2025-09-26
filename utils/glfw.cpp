#include "glfw.hpp"

// ========== VARIABLES ========== //

GLFWwindow* glfw::window = nullptr;
GLFWmonitor *glfw::monitor = nullptr;
const GLFWvidmode* glfw::vidMode = nullptr;

int glfw::windowWidth = 0, glfw::windowHeight = 0;
int glfw::wWBefore = 0, glfw::wHBefore = 0;
int glfw::windowXPos = 0, glfw::windowYPos = 0;

bool glfw::isFullscreen = false;

// ========== MAIN METHODS ========== //

void glfw::init ()
{
    glfwInit ();

    {
        glfwWindowHint (GLFW_SAMPLES, 4);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        #ifdef __APPLE__
            glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }

    monitor = glfwGetPrimaryMonitor ();
    vidMode = glfwGetVideoMode (monitor);

    windowWidth = vidMode->width * 0.5f;
    windowHeight = vidMode->height * 0.5f;

    window = glfwCreateWindow (windowWidth, windowHeight, "Rendering Bivariate Functions with OpenGL", NULL, NULL);
    glfwMakeContextCurrent (window);
    glfwSwapInterval (1);

    glfwSetKeyCallback (window, keyCallback);
    glfwSetCursorPosCallback (window, cursorPosCallback);
    glfwSetMouseButtonCallback (window, mouseButtonCallback);
    glfwSetFramebufferSizeCallback (window, framebufferSizeCallback);

    gladLoadGLLoader ((GLADloadproc)glfwGetProcAddress);

    framebufferSizeCallback (window, windowWidth, windowHeight);

    glEnable (GL_BLEND);
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_MULTISAMPLE);

    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    framebufferSizeCallback (window, windowWidth, windowHeight);
}

void glfw::terminate ()
{
    glfwTerminate ();
}

// ========== GLFW CALLBACKS ========== //

void glfw::framebufferSizeCallback (GLFWwindow *window, GLsizei width, GLsizei height)
{
        windowHeight = static_cast<int>(height);
        windowWidth = static_cast<int>(width);

    glViewport (0, 0, width, height);
    camera::setProjectionMatrix (static_cast<GLfloat>(width), static_cast<GLfloat>(height));
}

void glfw::keyCallback (GLFWwindow *window, int key, int scancode, int action, int mods)
{
    // ===== KEY :: F11 ===== //
    if ((key == GLFW_KEY_F11) && (action == GLFW_PRESS)) // FULLSCREEN
    {
        isFullscreen = !isFullscreen;

        if (isFullscreen)
        {
            glfwGetWindowPos (window, &windowXPos, &windowYPos);
            glfwGetWindowSize (window, &wWBefore, &wHBefore);

            glfwSetWindowMonitor (window, monitor, 0, 0, vidMode->width, vidMode->height, vidMode->refreshRate);
        }
        else
        {
            glfwSetWindowMonitor (window, NULL, windowXPos, windowYPos, wWBefore, wHBefore, 0);
        }
    }

    // ===== KEY :: ESC ===== //
    if ((key == GLFW_KEY_ESCAPE) && (action == GLFW_PRESS)) // CLOSE WINDOW
    {
        glfwSetWindowShouldClose (window, true);
    }
}

void glfw::cursorPosCallback (GLFWwindow *window, double xPos, double yPos)
{
    if (camera::cameraMode == true)
    {
        float xOffset = static_cast<float>(xPos) - camera::lastX,
        yOffset = camera::lastY - static_cast<float>(yPos);

        camera::lastX = xPos;
        camera::lastY = yPos;

        camera::setCursorPos (xOffset, yOffset);
    }
}

void glfw::mouseButtonCallback (GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT) // SWITCH CAMERA MODE
    {
        if (action == GLFW_PRESS) // ON
        {
            camera::cameraMode = true;

            double xPos, yPos;
            glfwGetCursorPos (window, &xPos, &yPos);

            camera::lastX = static_cast<float>(xPos);
            camera::lastY = static_cast<float>(yPos);

            glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else if (action == GLFW_RELEASE) // OFF
        {
            camera::cameraMode = false;

            glfwSetInputMode (window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}