#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <SFML/Graphics.hpp>

enum class Direction { Up, Down, Left, Right };

struct SnakeSegment {
    sf::Vector2i pos;
    SnakeSegment(int x, int y) : pos{ x,y } {}
};

class Snake {
    std::vector<SnakeSegment> body;
public:
    Direction dir = Direction::Right;
    Snake();
    void move(bool grow = false);
    bool checkSelfCollision() const;
    bool isAt(int x, int y) const;
    const std::vector<SnakeSegment>& getBody() const { return body; }
};

#endif
