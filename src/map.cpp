#include "map.h"

Map::Map(sf::RenderWindow *window, int cellSize)
{
    initVariables(cellSize);
    initComponents(window);
}

Map::~Map()
{
}

// Internal initializers.

void Map::initVariables(int cellSize)
{
    this->cellSize = cellSize;
}

void Map::initComponents(sf::RenderWindow *window)
{
    this->window = window;
    initTileMap();
}

void Map::initTileMap()
{
    int numTiles = this->window->getSize().x / this->cellSize;
    for (int i = 0; i < numTiles; i++)
    {
        for (int j = 0; j < numTiles; j++)
        {
            std::vector<int> index {i, j};
            tileMap[index] = new Tile(this->window,
                                      this->cellSize*i, 
                                      this->cellSize*j, 
                                      this->cellSize);
        }
    }
}

// Getters

int Map::getCellSize()
{
    return this->cellSize;
}

Tile* Map::getTile(int i, int j)
{
    std::vector<int> index {i,j};
    std::map<std::vector<int>,Tile*>::iterator it;
    it = this->tileMap.find(index);
    if (it != this->tileMap.end()) return it->second;
    else return nullptr;
}

// Setters

void Map::setCellSize(int cellSize)
{
    this->cellSize = cellSize;
}

void Map::setTileMode(int mode, int i, int j)
{
    Tile *tile = this->getTile(i, j);
    tile->setMode(mode);
}

sf::Vector2u Map::getTileIndex(float x, float y)
{
    int i = x / this->cellSize;
    int j = y / this->cellSize;
    return sf::Vector2u(i, j);
}

// Public Functions.

void Map::bindRenderWindow(sf::RenderWindow* window)
{
    this->window = window;
}

void Map::update()
{
    std::map<std::vector<int>,Tile*>::iterator it = this->tileMap.begin();
    while (it != this->tileMap.end())
    {
        it->second->refresh();
        ++it;
    }

}

void Map::render()
{
    std::map<std::vector<int>,Tile*>::iterator it = this->tileMap.begin();
    while (it != this->tileMap.end())
    {
        it->second->render();
        ++it;
    }
}
