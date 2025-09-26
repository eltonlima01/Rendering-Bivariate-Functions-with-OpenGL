#ifndef HEADERS_HPP
#define HEADERS_HPP

#include <iomanip>
#include <iostream>

#include "../include/imgui/imgui.h"
#include "../include/imgui/backends/imgui_impl_glfw.h"
#include "../include/imgui/backends/imgui_impl_opengl3.h"

#include "../utils/glfw.hpp"
#include "../model/world.hpp"
#include "../model/points.hpp"

char buf [256] = "(x * z * ((x * x) - (z * z))) / ((x * x) + (z * z))";

#endif