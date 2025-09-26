#include "world.hpp"

// ========== VARIABLES ========== //

Ground *world::ground = nullptr;
Axis *world::axis = nullptr;
Grid *world::grid = nullptr;

// ========== METHODS ========== //

void world::init ()
{
    axis = new Axis ();
    grid = new Grid ();
    ground = new Ground ();
}

void world::terminate ()
{
    delete axis;
    axis = nullptr;
    
    delete grid;
    grid = nullptr;
    
    delete ground;
    ground = nullptr;
}

void world::draw (glm::mat4 Projection, glm::mat4 View)
{
    axis->draw (Projection, View);
    grid->draw (Projection, View);
    ground->draw (Projection, View);
}