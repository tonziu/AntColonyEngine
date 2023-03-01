#include "engine.h"

Engine::Engine()
{
    initVariables();
    initComponents();
}

Engine::~Engine()
{
    delete this->window;
    delete this->map;
}

// INTERNAL INITIALIZERS 
void Engine::initComponents()
{
    this->window = nullptr;
    this->map = nullptr;
    this->colony = nullptr;
}

void Engine::initVariables()
{
    this->shouldClose = false;
}

// PRIVATE FUNCTIONS
void Engine::processInput()
{
    sf::Event event;
    while (this->window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            this->shouldClose = true;
            break;
        default:
            break;
        }
    }
}

void Engine::update()
{
    if (this->colony) this->colony->update();
    if (this->map) this->map->update();
}

void Engine::render()
{
    this->window->clear(sf::Color::Black);
    if (this->map) this->map->render();
    if (this->colony) this->colony->render();
    this->window->display();
}

// PUBLIC FUNCTIONS 

void Engine::setFPS(int FPS)
{
    if (this->window) this->window->setFramerateLimit(FPS);
}

void Engine::createWindow(int width, int height, const char* title)
{
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), title);
}

void Engine::createMap(int cellSize)
{
    this->map = new Map(this->window, cellSize);
}

void Engine::createNest(int i0, int j0, int nestSize)
{
    // get a tile from the map at desired location.
    for (int i = i0; i < i0 + nestSize; ++i)
    {
        for (int j = j0; j < j0 + nestSize; ++j)
        {
            Tile *tile = this->map->getTile(i, j);
            tile->setMode(NEST);
        }
    }
}

void Engine::createFood(int i0, int j0, int foodSize)
{
    for (int i = i0; i < i0 + foodSize; ++i)
    {
        for (int j = j0; j < j0 + foodSize; ++j)
        {
            Tile *tile = this->map->getTile(i, j);
            tile->setMode(FOOD);
        }
    }
}

void Engine::createColony()
{
    this->colony = new Colony(this->window, this->map);
}

void Engine::runSimulation()
{
    while (!this->shouldClose)
    {
        this->processInput();
        this->update();
        this->render();
    }

    this->window->close();
}
