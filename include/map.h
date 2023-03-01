#ifndef MAP_H
#define MAP_H

#include "tile.h"

class Map
{
    private:
        //Internal components.
        sf::RenderWindow *window;
        std::map<std::vector<int>, Tile*> tileMap;
        
        // Internal Variables.
        int cellSize;

        /* Internal Initializers. */
        void initVariables(int cellSize);
        void initComponents(sf::RenderWindow *window);
        void initTileMap();

    public:
        /*Constructor and Destructor. */
        Map(sf::RenderWindow *window, int cellSize);
        ~Map();

        /*Getters.*/
        int getCellSize();
        Tile* getTile(int i, int j);
        sf::Vector2u getTileIndex(float x, float y);

        /*Setters.*/
        void setCellSize(int cellSize);
        void setTileMode(int mode, int i, int j);

        /* Public functions. */
        void bindRenderWindow(sf::RenderWindow *window);
        
        void update();
        void render();

};

#endif // MAP_H 
