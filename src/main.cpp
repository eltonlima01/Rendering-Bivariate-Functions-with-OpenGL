#include "headers.hpp"

int main ()
{
    glfw::init ();
    world::init ();
    
    Points *points = new Points ();

    glEnable (GL_DEPTH_TEST);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    lastTime = glfwGetTime ();

    while (glfwWindowShouldClose (glfw::window) == false)
    {
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor (0.85f, 0.85f, 0.85f, 1.0f);

        points->draw (camera::getProjectionMatrix (), camera::getViewMatrix ());
        world::draw (camera::getProjectionMatrix (), camera::getViewMatrix ());

        setNumberFrames (glfw::window);

        glfwPollEvents ();
        glfwSwapBuffers (glfw::window);
    }

    delete points;
    points = nullptr;

    world::terminate ();

    glfwTerminate ();
    return 0;
}