#include <arkenoid.hpp>

#define MAX_FRAMERATE_LIMIT 60
#define ANTI_ALIASING_LEVEL 10
#define ICON_IMAGE_PATH "res/images/icon.png"

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
        window.draw(ball.shape);
        window.display();
    }

    return EXIT_SUCCESS;
}