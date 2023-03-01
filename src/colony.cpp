#include "colony.h"

Colony::Colony(sf::RenderWindow *window, Map *map)
{
    this->window = window;
    this->map = map;
    this->initAnts();
}

Colony::~Colony()
{
}

void Colony::initAnts()
{
    for (int i = 0; i < N; i++)
    {
        this->ants[i].init(this->window,
                           this->map, 
                           this->window->getSize().x / 2,
                           this->window->getSize().y / 2,
                           ANT_WIDTH,
                           ANT_HEIGHT,
                           rand() % 360,
                           ANT_SPEED,
                           STEER_ANGLE,
                           SENSE_ANGLE,
                           SENSE_DIST);
    }
}

void Colony::update()
{
    for (int i = 0; i < N; i++)
    {
        this->ants[i].update();
    }
}

void Colony::render()
{
    for (int i = 0; i < N; i++)
    {
        this->ants[i].render();
    }
}
