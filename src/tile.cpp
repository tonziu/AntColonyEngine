#include "tile.h"

Tile::Tile(sf::RenderWindow *window, int x, int y, int cellSize)
{
    initVariables(x, y, cellSize);
    initComponents(window);
}

Tile::~Tile()
{
}

// Internal initializers.

void Tile::initVariables(int x, int y, int cellSize)
{
    this->x = x;
    this->y = y;
    this->w = cellSize;
    this->h = cellSize;
    this->mode = VOID;
    this->amount = 0;
}

void Tile::initComponents(sf::RenderWindow *window)
{
    this->window = window;
    this->rect.setPosition(sf::Vector2f(this->x, this->y));
    this->rect.setSize(sf::Vector2f(this->w, this->h));
    this->rect.setFillColor(sf::Color::Black);
}

// Getters.

sf::Vector2u Tile::getPosition()
{
    return sf::Vector2u(this->x, this->y);
}

int Tile::getMode()
{
    return this->mode;
}

float Tile::getAmount()
{
    return this->amount;
}

// Setters. 
void Tile::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    this->rect.setPosition(sf::Vector2f(this->x, this->y));
}

void Tile::addAmount(int amount)
{
    this->amount += amount;
}

void Tile::setMode(int mode)
{
    this->mode = mode;
    switch (mode)
    {
        case VOID:
            {
                this->setColor(sf::Color::Black);
                this->amount = 0;
            }
            break;
        case NEST:
            {
                this->setColor(sf::Color(0, 0, 200));
                this->amount = 1000;
            }
            break;
        case FOOD:
            {
                this->setColor(sf::Color::Green);
                this->amount = 1000;
            }
            break;
        case NEST_TRAIL:
            {
                this->setColor(sf::Color::Blue);
            }
            break;
        case FOOD_TRAIL:
            {
                this->setColor(sf::Color::Red);
            }
            break;
        default:
            break;
    }
}

void Tile::setColor(sf::Color color)
{
    this->rect.setFillColor(color);
}

// Public Functions. 

void Tile::refresh()
{
    if (this->mode == NEST_TRAIL || this->mode == FOOD_TRAIL)
    {
        if (this->amount > 0)
        {
            amount -= 0.2;
        }
        else if (this->amount <= 0)
        {
            this->setMode(VOID);
        }
    }
}

void Tile::render()
{
    this->window->draw(this->rect);
}
