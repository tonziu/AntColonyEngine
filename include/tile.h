#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <map>
#include <math.h>
#include <random>
#include <algorithm>
#include <initializer_list>

typedef std::mt19937 RNG;

static std::random_device rd;
static RNG rng{rd()};

enum TILE_MODE {VOID = 0, NEST, FOOD, NEST_TRAIL, FOOD_TRAIL};

class Tile
{
    private:
        // Internal Variables. 
        int x, y;
        int w, h;
        int mode;
        float amount;

        // Internal Components.
        sf::RenderWindow *window;
        sf::RectangleShape rect;
        
        // Internal initializers. 
        void initVariables(int x, int y, int cellSize);
        void initComponents(sf::RenderWindow *window);

    public:
        // Constructor and Destructor.
        Tile(sf::RenderWindow *window, int x, int y, int cellSize);
        ~Tile();

        // Getters 
        sf::Vector2u getPosition();

        int getMode();
        float getAmount();
        
        // Setters
        void setPosition(int x, int y);
        void setColor(sf::Color);
        void setMode(int mode);

        // Public functions.
        void refresh();
        void addAmount(int amount);
        void render();
};

#endif // TILE_H
