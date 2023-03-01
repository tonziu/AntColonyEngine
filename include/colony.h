#ifndef COLONY_H
#define COLONY_H

#include "ant.h"

#define N 200

#define ANT_WIDTH 5
#define ANT_HEIGHT 2
#define ANT_SPEED 5
#define STEER_ANGLE 20
#define SENSE_ANGLE 30
#define SENSE_DIST 15


class Colony
{
    private:
        sf::RenderWindow *window;
        Map *map;
        Ant ants[N];

        void initAnts();

    public:
        Colony(sf::RenderWindow *window, Map *map);
        ~Colony();

        void update();
        void render();
};



#endif // COLONY_H
