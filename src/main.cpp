#include <arkenoid.hpp>

#define MAX_FRAMERATE_LIMIT 60
#define ANTI_ALIASING_LEVEL 10
#define ICON_IMAGE_PATH "res/images/icon.png"

constexpr int xBricks{11}, yBricks{4};
const sf::Vector2f brickSize = {60.0f, 20.0f};

void check_collision(ar::Paddle &mPaddle, ar::Ball &mBall)
{
    // do nothing if no collision
    if (!ar::isIntersecting(mPaddle, mBall)) return;

    // reverse velocity in the y dimension
    mBall.velocity.y = -mBall.velocity.y;
    
    if (mBall.x() > mPaddle.x()) mBall.velocity.x = mBall.ballVelocity;
    else mBall.velocity.x = -mBall.ballVelocity;
}

int main()
{
    // globally enable antialiasing, make the edges of shapes smoother
    // (if supported by the grahpics card)
    sf::ContextSettings settings;
    settings.antialiasingLevel = ANTI_ALIASING_LEVEL;

    // get desktop width and height
    const auto screenWidth = sf::VideoMode::getDesktopMode().width;
    const auto screenHeight = sf::VideoMode::getDesktopMode().height;

    // init window
    sf::RenderWindow window(
        sf::VideoMode(screenWidth, screenHeight),
        "Asteroids",
        sf::Style::Default,
        settings);
    // limit frame rate to max value
    window.setFramerateLimit(MAX_FRAMERATE_LIMIT);

    // set window icon 
    auto image = sf::Image{};
    if (!image.loadFromFile(ICON_IMAGE_PATH))
    {
        // failed to load icon image
        return EXIT_FAILURE;
    }
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());

    // create ball entity 
    ar::Ball ball{
        sf::Vector2f(screenWidth / 2, screenHeight / 2), 
        sf::Vector2f(screenWidth, screenHeight)
        };
    
    // create paddle entity 
    ar::Paddle paddle{
        sf::Vector2f(screenWidth / 2, screenHeight - 100 ), 
        sf::Vector2f(screenWidth, screenHeight)
    };

    // create bunch of bricks entities
    // in grid fashion
    std::vector <ar::Brick> bricks;
    for (int x{0}; x <= xBricks; ++x)
        for (int y{0}; y < yBricks; ++y)
        {
            bricks.emplace_back(
                sf::Vector2f((x + 1) * (brickSize.x + 42) + 22, (y + 2) * (brickSize.y + 6)),
                brickSize
            );

        }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);

        ball.update();
        paddle.update();

        check_collision(paddle, ball);
        
        window.draw(ball.shape);
        window.draw(paddle.shape);
        for(auto& brick: bricks) window.draw(brick.shape);
        
        window.display();
    }

    return EXIT_SUCCESS;
}