#include <SFML/Graphics.hpp>
#include "snake.h"
#include "food.h"
#include <ctime>
#include <cstdlib>
#include <optional>
#include <string>
#include <iostream>

constexpr int TILE = 20;
constexpr int W = 40;
constexpr int H = 40;
constexpr int WIDTH = W * TILE;
constexpr int HEIGHT = H * TILE;

int main() {

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::VideoMode videoMode(sf::Vector2u{ WIDTH, HEIGHT });
    sf::RenderWindow window(videoMode, sf::String("Snake"), sf::Style::Default);
    int currentFramerate = 15;
    int lastScoreCheckpoint = 0;
    window.setFramerateLimit(currentFramerate);


    Snake snake;
    Food food;
    food.respawn(snake, W, H);

    bool grow = false;
    int score = 0;


    sf::Font font("arial.ttf");

    // Tekst punktów
    sf::Text scoreText{ font };
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(sf::Vector2f{ 5.f, 2.f });

    // Tekst końca gry
    sf::Text gameOverText{ font };
    gameOverText.setString("KONIEC GRY");
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    
    gameOverText.setPosition(sf::Vector2f(5.f, 2.f));

    while (window.isOpen()) {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && snake.dir != Direction::Down)
            snake.dir = Direction::Up;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && snake.dir != Direction::Up)
            snake.dir = Direction::Down;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && snake.dir != Direction::Right)
            snake.dir = Direction::Left;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && snake.dir != Direction::Left)
            snake.dir = Direction::Right;

        snake.move(grow);
        grow = false;

        if (snake.getBody().front().pos == food.pos) {
            grow = true;
            score += 10;
            food.respawn(snake, W, H);
        }

        auto headPos = snake.getBody().front().pos;
        if (headPos.x < 0 || headPos.x >= W || headPos.y < 0 || headPos.y >= H
            || snake.checkSelfCollision()) {

            // Wyświetlenie końca gry
            window.clear(sf::Color::Black);
            window.draw(gameOverText);
            window.display();
            sf::sleep(sf::seconds(3));
            window.close();
            break;
        }

       

        window.clear(sf::Color::Black);

        sf::RectangleShape block(sf::Vector2f(static_cast<float>(TILE - 2), static_cast<float>(TILE - 2)));
        block.setFillColor(sf::Color::Green);
        for (const auto& seg : snake.getBody()) {
            block.setPosition(sf::Vector2f(static_cast<float>(seg.pos.x * TILE), static_cast<float>(seg.pos.y * TILE)));
            window.draw(block);
        }

        block.setFillColor(sf::Color::Red);
        block.setPosition(sf::Vector2f(static_cast<float>(food.pos.x * TILE), static_cast<float>(food.pos.y * TILE)));
        window.draw(block);

        scoreText.setString("Score: " + std::to_string(score));
        window.draw(scoreText);

       
        if (score - lastScoreCheckpoint >= 50) {
            currentFramerate += 5;
            if (currentFramerate > 120) currentFramerate = 120; // opcjonalny limit maksymalny
            window.setFramerateLimit(currentFramerate);
            lastScoreCheckpoint = score;
        }



        window.display();
    }

    return 0;
}
