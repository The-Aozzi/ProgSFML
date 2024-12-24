#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int PADDLE_WIDTH = 20;
const int PADDLE_HEIGHT = 100;
const int BALL_RADIUS = 10;
const float PADDLE_SPEED = 5.0f;
const float BALL_SPEED = 5.0f;


int WinMain() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2-Player Ping Pong", sf::Style::Close);
    window.setFramerateLimit(60);

    // Paddles
    sf::RectangleShape leftPaddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    sf::RectangleShape rightPaddle(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
    leftPaddle.setPosition(50, (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2);
    rightPaddle.setPosition(WINDOW_WIDTH - 50 - PADDLE_WIDTH, (WINDOW_HEIGHT - PADDLE_HEIGHT) / 2);

    // Ball
    sf::CircleShape ball(BALL_RADIUS);
    ball.setPosition((WINDOW_WIDTH - BALL_RADIUS * 2) / 2, (WINDOW_HEIGHT - BALL_RADIUS * 2) / 2);

    // Ball velocity
    sf::Vector2f ballVelocity(-BALL_SPEED, -BALL_SPEED);

    // Scores
    int leftScore = 0;
    int rightScore = 0;

    // Font and text for scores
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font!\n";
        return -1;
    }
    sf::Text leftScoreText;
    sf::Text rightScoreText;
    leftScoreText.setFont(font);
    rightScoreText.setFont(font);
    leftScoreText.setCharacterSize(30);
    rightScoreText.setCharacterSize(30);
    leftScoreText.setPosition(200, 20);
    rightScoreText.setPosition(600, 20);

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Player 1 controls (W/S)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && leftPaddle.getPosition().y > 0) {
            leftPaddle.move(0, -PADDLE_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && leftPaddle.getPosition().y + PADDLE_HEIGHT < WINDOW_HEIGHT) {
            leftPaddle.move(0, PADDLE_SPEED);
        }

        // Player 2 controls (Up/Down)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rightPaddle.getPosition().y > 0) {
            rightPaddle.move(0, -PADDLE_SPEED);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rightPaddle.getPosition().y + PADDLE_HEIGHT < WINDOW_HEIGHT) {
            rightPaddle.move(0, PADDLE_SPEED);
        }

        // Ball movement
        ball.move(ballVelocity);

        // Ball collision with top and bottom walls
        if (ball.getPosition().y <= 0 || ball.getPosition().y + BALL_RADIUS * 2 >= WINDOW_HEIGHT) {
            ballVelocity.y = -ballVelocity.y;
        }

        // Ball collision with paddles
        if (ball.getGlobalBounds().intersects(leftPaddle.getGlobalBounds()) ||
            ball.getGlobalBounds().intersects(rightPaddle.getGlobalBounds())) {
            ballVelocity.x = -ballVelocity.x;
        }

        // Ball out of bounds (score)
        if (ball.getPosition().x <= 0) {
            rightScore++;
            ball.setPosition((WINDOW_WIDTH - BALL_RADIUS * 2) / 2, (WINDOW_HEIGHT - BALL_RADIUS * 2) / 2);
            ballVelocity = sf::Vector2f(BALL_SPEED, BALL_SPEED);
        }
        if (ball.getPosition().x + BALL_RADIUS * 2 >= WINDOW_WIDTH) {
            leftScore++;
            ball.setPosition((WINDOW_WIDTH - BALL_RADIUS * 2) / 2, (WINDOW_HEIGHT - BALL_RADIUS * 2) / 2);
            ballVelocity = sf::Vector2f(-BALL_SPEED, -BALL_SPEED);
        }

        // Update score texts
        leftScoreText.setString(std::to_string(leftScore));
        rightScoreText.setString(std::to_string(rightScore));

        // Clear the window
        window.clear();

        // Draw everything
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(ball);
        window.draw(leftScoreText);
        window.draw(rightScoreText);

        // Display
        window.display();
    }

    return 0;
}
