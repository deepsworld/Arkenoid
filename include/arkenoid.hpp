#pragma once 

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace ar
{

    class Ball
    {
        private:
            const float ballRadius = 10.0f;
            const float ballVelocity = 8.0f;

            sf::Vector2f windowSize;

            void setWindowSize(sf::Vector2f aWindowSize)
            {
                windowSize.x = aWindowSize.x;
                windowSize.y = aWindowSize.y;
            }

        public: 
            sf::CircleShape shape;
            sf::Vector2f velocity {-ballVelocity, -ballVelocity};

            Ball(sf::Vector2f aPos, sf::Vector2f aWindowSize)
            {
                shape.setPosition(aPos);
                shape.setRadius(ballRadius);
                shape.setFillColor(sf::Color::Red);
                shape.setOrigin(ballRadius, ballRadius);
                setWindowSize(aWindowSize);
            }

            // move the ball 
            void update() { 
                shape.move(velocity); 

                /*
                 left: move ball towards right (+tive velocity)
                 right: move ball towards left (-tive velocity)
                 ....
                */
                if (left() < 0.f){ velocity.x = ballVelocity; }
                if (right() > windowSize.x) { velocity.x = -ballVelocity; }
                if (top() < 0.f) { velocity.y = ballVelocity; }
                if (bottom() > windowSize.y) { velocity.y = -ballVelocity; }

            }

            // x, y: centre or origin of the ball
            float x() { return shape.getPosition().x; }
            float y() { return shape.getPosition().y; }
            // left, right, top and bottom of the ball
            float left() { return x() - shape.getRadius(); }
            float right() { return x() + shape.getRadius(); }
            float top() {return y() - shape.getRadius(); }
            float bottom() { return y() + shape.getRadius(); }
    };

}