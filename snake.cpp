#include "snake.h"

Snake::Snake() {
    body.emplace_back(5, 5);
}

void Snake::move(bool grow) {
    auto head = body.front().pos;
    switch (dir) {
    case Direction::Up: head.y--; break;
    case Direction::Down: head.y++; break;
    case Direction::Left: head.x--; break;
    case Direction::Right: head.x++; break;
    }
    body.insert(body.begin(), SnakeSegment(head.x, head.y));
    if (!grow) body.pop_back();
}

bool Snake::checkSelfCollision() const {
    auto head = body.front().pos;
    for (size_t i = 1; i < body.size(); ++i)
        if (body[i].pos == head) return true;
    return false;
}

bool Snake::isAt(int x, int y) const {
    for (auto& s : body)
        if (s.pos.x == x && s.pos.y == y) return true;
    return false;
}
