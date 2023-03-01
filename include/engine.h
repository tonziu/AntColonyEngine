#ifndef ENGINE_H
#define ENGINE_H

#include "colony.h"

class Engine
{
    private:
        // Components.
        sf::RenderWindow *window; // main window 
        Map *map;
        Colony *colony;

        // Internal variables.
        bool shouldClose;

        // Internal initializers.
        void initVariables();
        void initComponents();

        // Internal Functions.
        void processInput();
        void update();
        void render();

    public:
        // Constructor and Destructor.
        Engine();
        ~Engine();

        // Create a window of a fixed size.
        void createWindow(int width, int height, const char* title);

        void setFPS(int FPS);

        // Create a map of a fixed cell size in pixel units.
        void createMap(int cellSize);

        // Create a nest indicating the upper-left index and size.
        void createNest(int i0, int j0, int nestSize);

        // Create a food indicating the upper-left index and size.
        void createFood(int i0, int j0, int foodSize);

        void createColony();

        // Show the window until it is closed.
        void runSimulation();
};

#endif /* ENGINE_H */
