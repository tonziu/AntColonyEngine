#include "ant.h"

Ant::Ant()
{
    this->x = -1;
    this->y = -1;
    this->width = 0;
    this->height = 0;
    this->dir = 0;
    this->speed = 0;
    this->steerAngle = 0;
    this->senseAngle = 0;
    this->senseDistance = 0;
    this->mode = EXPLORING;
    this->window = nullptr;
    this->map = nullptr;
    this->rect.setPosition(sf::Vector2f(this->x, this->y));
    this->rect.setSize(sf::Vector2f(this->width, this->height));
    this->rect.setOrigin(sf::Vector2f(this->width/2, this->height/2));
    this->rect.setFillColor(sf::Color::White);
}

Ant::~Ant()
{
}

void Ant::init(sf::RenderWindow *window, 
               Map *map, 
               float x,
               float y,
               float w,
               float h,
               float dir,
               float speed,
               float steerAngle,
               float senseAngle,
               float senseDistance)
{
    this->x = x;
    this->y = y;
    this->width = w;
    this->height = h;
    this->dir = dir;
    this->speed = speed;
    this->steerAngle = steerAngle;
    this->senseAngle = senseAngle;
    this->senseDistance = senseDistance;
    this->mode = EXPLORING;
    this->window = window;
    this->map = map;
    this->rect.setPosition(sf::Vector2f(this->x, this->y));
    this->rect.setSize(sf::Vector2f(this->width, this->height));
    this->rect.setOrigin(sf::Vector2f(this->width/2, this->height/2));
    this->rect.setFillColor(sf::Color::White);
}

// Internal functions 

int Ant::getRandomInt(int max)
{
    static std::uniform_int_distribution<int> uid(0, max);
    return uid(rng);
}

void Ant::avoidBorders()
{
    if (this->x < 0 || this->x > this->window->getSize().x)
    {
        this->dir += 90;
    }

    if (this->y < 0 || this->y > this->window->getSize().y)
    {
        this->dir += 90;
    }
}

void Ant::updateRect()
{
    this->rect.setPosition(sf::Vector2f(this->x, this->y));
    this->rect.setRotation(this->dir);
}

void Ant::move()
{
    this->x += this->speed * cos(this->dir * M_PI / 180);
    this->y += this->speed * sin(this->dir * M_PI / 180);
    this->avoidBorders();
    this->updateRect();
}

void Ant::depositTrail()
{
    float amount = 0;
    float depositThreshold = 0.1;
    switch (this->mode)
    {
        case EXPLORING:
            {
                if (this->homeTrailTimer.getElapsedTime().asSeconds() > depositThreshold)
                {
                    Tile *curr = this->getTile(); 
                    if (curr)
                    {
                        if (curr->getMode() == VOID)
                        {
                            sf::Vector2u index = this->map->getTileIndex(curr->getPosition().x, curr->getPosition().y);
                            this->map->setTileMode(NEST_TRAIL, index.x, index.y);
                            amount = 50 / this->leftHomeTimer.getElapsedTime().asSeconds();
                            curr->addAmount(amount);
                        }
                        else if (curr->getMode() == NEST_TRAIL)
                        {
                            amount = 50 / this->leftHomeTimer.getElapsedTime().asSeconds();
                            curr->addAmount(amount);
                        }
                        this->homeTrailTimer.restart();
                    }
                }
            }
            break;
        case RETURNING:
            {
                if (this->foodTrailTimer.getElapsedTime().asSeconds() > depositThreshold)
                {
                    Tile *curr = this->getTile(); 
                    if (curr)
                    {
                        if (curr->getMode() == VOID)
                        {
                            sf::Vector2u index = this->map->getTileIndex(curr->getPosition().x, curr->getPosition().y);
                            this->map->setTileMode(FOOD_TRAIL, index.x, index.y);
                            amount = 50 / this->leftHomeTimer.getElapsedTime().asSeconds();
                            curr->addAmount(amount);
                        }
                        else if (curr->getMode() == FOOD_TRAIL)
                        {
                            amount = 50 / this->leftHomeTimer.getElapsedTime().asSeconds();
                            curr->addAmount(amount);
                        }
                        this->foodTrailTimer.restart();
                    }
                }

            }
            break;
        default:
            break;
    }
}

void Ant::updateMode()
{
    switch (this->mode)
    {
        case EXPLORING:
        {
            Tile *curr = this->getTile();
            if (curr) 
            {
                if (curr->getMode() == FOOD)
                {
                    this->mode = RETURNING;
                    this->leftHomeTimer.restart();
                    this->eat(curr);
                    this->dir += 180;
                }
            }
        }
        break;
        case RETURNING:
        {
            Tile *curr = this->getTile();
            if (curr) 
            {
                if (curr->getMode() == NEST)
                {
                    this->mode = EXPLORING;
                    this->leftHomeTimer.restart();
                    this->dir += 180;
                }
            }
        }
        break;
        default:
            break;
    }
}

void Ant::eat(Tile *tile)
{
    if (tile->getMode() == FOOD)
    {
        tile->setMode(VOID);
    }
}

void Ant::steerRandomly()
{
    int randomAngle = this->getRandomInt(this->steerAngle);
    this->dir += randomAngle - this->steerAngle/2;
}

void Ant::senseTrail()
{
    float rotAngle = 0;
    float leftAmount = 0;
    float centerAmount = 0;
    float rightAmount = 0;
    int N = 3;

    switch (this->mode)
    {
        case EXPLORING:
            {
                float x1 = this->rect.getPosition().x + this->senseDistance * cos((this->dir - this->senseAngle) * M_PI/180); 
                float y1 = this->rect.getPosition().y + this->senseDistance * sin((this->dir - this->senseAngle) * M_PI/180);

                float x2 = this->rect.getPosition().x + this->senseDistance * cos(this->dir * M_PI/180);
                float y2 = this->rect.getPosition().y + this->senseDistance * sin(this->dir * M_PI/180);

                float x3 = this->rect.getPosition().x + this->senseDistance * cos((this->dir + this->senseAngle) * M_PI/180);
                float y3 = this->rect.getPosition().y + this->senseDistance * sin((this->dir + this->senseAngle) * M_PI/180);

                sf::Vector2u index1 = this->map->getTileIndex(x1, y1);
                sf::Vector2u index2 = this->map->getTileIndex(x2, y2);
                sf::Vector2u index3 = this->map->getTileIndex(x3, y3);

                for (int i = -N; i < N; i++)
                {
                    for (int j = -N; j < N; j++)
                    {
                        sf::Vector2u leftIndex = index1 + sf::Vector2u(i, j);
                        sf::Vector2u centerIndex = index2 + sf::Vector2u(i, j);
                        sf::Vector2u rightIndex = index3 + sf::Vector2u(i, j);
                        Tile *leftTile = this->map->getTile(leftIndex.x, leftIndex.y);
                        Tile *centerTile = this->map->getTile(centerIndex.x, centerIndex.y);
                        Tile *rightTile = this->map->getTile(rightIndex.x, rightIndex.y);
                        if (leftTile)
                        {
                            if (leftTile->getMode() == FOOD_TRAIL || leftTile->getMode() == FOOD)
                                leftAmount += leftTile->getAmount();
                        }
                        if (centerTile)
                        {
                            if (centerTile->getMode() == FOOD_TRAIL || centerTile->getMode() == FOOD)
                                centerAmount += centerTile->getAmount();
                        }
                        if (rightTile) 
                        {
                            if (rightTile->getMode() == FOOD_TRAIL || rightTile->getMode() == FOOD)
                                rightAmount += rightTile->getAmount();
                        }
                    }
                }



                /*Tile *tile1 = this->map->getTile(index1.x, index1.y);
                Tile *tile2 = this->map->getTile(index2.x, index2.y);
                Tile *tile3 = this->map->getTile(index3.x, index3.y);

                float amount1 = 0;
                float amount2 = 0;
                float amount3 = 0;

                if (tile1) 
                {
                    amount1 = (tile1->getMode() == FOOD_TRAIL) ? tile1->getAmount() : 0;
                    tile1->setColor(sf::Color::White);
                }
                if (tile2)
                {
                    amount2 = (tile2->getMode() == FOOD_TRAIL) ? tile2->getAmount() : 0;
                }
                if (tile3)
                {
                    amount3 = (tile3->getMode() == FOOD_TRAIL) ? tile3->getAmount() : 0;
                }*/

                float maxAmount = std::max({leftAmount, centerAmount, rightAmount});
                
                if (maxAmount != 0)
                {
                    if (maxAmount == leftAmount)
                    {
                        rotAngle = this->dir - this->senseAngle;
                    }
                    else if (maxAmount == centerAmount)
                    {
                        rotAngle = this->dir;
                    }
                    else
                    {
                        rotAngle = this->dir + this->senseAngle;
                    }

                    this->dir = rotAngle;
                }
            }
            break;
        case RETURNING:
            {
                float x1 = this->rect.getPosition().x + this->senseDistance * cos((this->dir - this->senseAngle) * M_PI/180); 
                float y1 = this->rect.getPosition().y + this->senseDistance * sin((this->dir - this->senseAngle) * M_PI/180);

                float x2 = this->rect.getPosition().x + this->senseDistance * cos(this->dir * M_PI/180);
                float y2 = this->rect.getPosition().y + this->senseDistance * sin(this->dir * M_PI/180);

                float x3 = this->rect.getPosition().x + this->senseDistance * cos((this->dir + this->senseAngle) * M_PI/180);
                float y3 = this->rect.getPosition().y + this->senseDistance * sin((this->dir + this->senseAngle) * M_PI/180);

                sf::Vector2u index1 = this->map->getTileIndex(x1, y1);
                sf::Vector2u index2 = this->map->getTileIndex(x2, y2);
                sf::Vector2u index3 = this->map->getTileIndex(x3, y3);
                
                for (int i = -N; i < N; i++)
                {
                    for (int j = -N; j < N; j++)
                    {
                        sf::Vector2u leftIndex = index1 + sf::Vector2u(i, j);
                        sf::Vector2u centerIndex = index2 + sf::Vector2u(i, j);
                        sf::Vector2u rightIndex = index3 + sf::Vector2u(i, j);
                        Tile *leftTile = this->map->getTile(leftIndex.x, leftIndex.y);
                        Tile *centerTile = this->map->getTile(centerIndex.x, centerIndex.y);
                        Tile *rightTile = this->map->getTile(rightIndex.x, rightIndex.y);
                        if (leftTile)
                        {
                            if (leftTile->getMode() == NEST_TRAIL || leftTile->getMode() == NEST)
                                leftAmount += leftTile->getAmount();
                        }
                        if (centerTile)
                        {
                            if (centerTile->getMode() == NEST_TRAIL || centerTile->getMode() == NEST)
                                centerAmount += centerTile->getAmount();
                        }
                        if (rightTile) 
                        {
                            if (rightTile->getMode() == NEST_TRAIL || rightTile->getMode() == NEST)
                                rightAmount += rightTile->getAmount();
                        }
                    }
                }

                float maxAmount = std::max({leftAmount, centerAmount, rightAmount});
                
                if (maxAmount != 0)
                {
                    if (maxAmount == leftAmount)
                    {
                        rotAngle = this->dir - this->senseAngle;
                    }
                    else if (maxAmount == centerAmount)
                    {
                        rotAngle = this->dir;
                    }
                    else
                    {
                        rotAngle = this->dir + this->senseAngle;
                    }

                    this->dir = rotAngle;
                }     
            }
        break;
        default:
        break;
    }
}

// Accessible functions

Tile* Ant::getTile()
{
    sf::Vector2u index = this->map->getTileIndex(this->x, this->y); 
    Tile *tile = this->map->getTile(index.x, index.y);
    return tile;
}

void Ant::update()
{
    this->steerRandomly();
    float notChange = rand()%100 - 100 * (WANDER_PROB);
    if (notChange > 0) 
    {
        this->senseTrail();
    }

    this->move();
    this->depositTrail();
    this->updateMode();
}

void Ant::render()
{
    this->window->draw(this->rect);
}
