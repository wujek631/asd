#include "food.h"
#include <cstdlib>

void Food::respawn(const Snake& snake, int w, int h) {
    do {
        pos.x = rand() % w;
        pos.y = rand() % h;
    } while (snake.isAt(pos.x, pos.y));
}
