#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <iomanip>
#include <iostream>

#include "../utils/glfw.hpp"

#include "../utils/glfw.hpp"
#include "../model/world.hpp"
#include "../model/Points.hpp"

double lastTime;
int frames = 0;

void setNumberFrames (GLFWwindow *window)
{
    frames++;
    double currentTime = glfwGetTime ();

    if (currentTime - lastTime >= 1.0)
    {
        double FRAMES_PER_SEC = (double)frames / (currentTime - lastTime);

        std::stringstream String;;

        String << "NULL | FPS: " << std::fixed << std::setprecision (1) << FRAMES_PER_SEC;

        glfwSetWindowTitle (window, String.str ().c_str ());

        lastTime = currentTime;
        frames = 0;
    }
}

#endif