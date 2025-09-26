#ifndef WORLD_HPP
#define WORLD_HPP

#include "private/Axis.hpp"
#include "private/Grid.hpp"
#include "private/Ground.hpp"

class world
{
    public:
        static void init ();
        static void terminate ();

        static void draw (glm::mat4 Projection, glm::mat4 View);

    private:
        static Ground *ground;
        static Grid *grid;
        static Axis *axis;
};

#endif