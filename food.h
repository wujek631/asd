#ifndef FOOD_H
#define FOOD_H

#include "snake.h"

class Food {
public:
    sf::Vector2i pos;
    void respawn(const Snake& snake, int w, int h);
};

#endif
