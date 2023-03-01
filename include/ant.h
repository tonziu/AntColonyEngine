#ifndef ANT_H
#define ANT_H

#include "map.h"

#define WANDER_PROB 0.1

enum ANT_MODE {EXPLORING = 0, RETURNING};

class Ant
{
        // Internal variables.
        float x, y;
        float width, height;
        float dir;
        float speed;
        float steerAngle;
        float senseAngle;
        float senseDistance;
        int mode;

        // Internal components.
        sf::RenderWindow* window;
        sf::RectangleShape rect;
        Map *map;

        sf::Clock homeTrailTimer;
        sf::Clock foodTrailTimer;
        sf::Clock leftHomeTimer;

        // Internal functions
        int getRandomInt(int max);
        int getSteeringBool();
        
        void avoidBorders();
        void depositTrail();
        void updateMode();
        void updateRect();
        void move();
        void eat(Tile *tile);
        void steerRandomly();
        void senseTrail();

    public:
        //Constructor and Destructor
        Ant();

        ~Ant();

        // Accessible functions
        Tile* getTile(); 

        void init(sf::RenderWindow *window, 
               Map *map, 
               float x,
               float y,
               float w,
               float h,
               float dir,
               float speed,
               float steerAngle,
               float senseAngle,
               float senseDistance);

        void update();
        void render();

};

#endif // ANT_H
