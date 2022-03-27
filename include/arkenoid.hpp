#pragma once 

#include <cmath>
#include <iostream>

#include <SFML/Graphics.hpp>

namespace ar
{

    /**
     * @brief Check collision between two entities
     * 
     * @tparam T1 
     * @tparam T2 
     * @param mA 
     * @param mB 
     * @return true 
     * @return false 
     */
    template <class T1, class T2> bool isIntersecting(T1& mA, T2& mB)
    {
        return  mA.right() >= mB.left() && \
                mA.bottom() >= mB.top() && \
                mA.left() <= mB.right() && \
                mA.top() <= mB.bottom();
    }

    class Brick
    {
        private:
            bool isDestroyed = false; 
            
        public: 
            sf::RectangleShape shape;

            Brick(sf::Vector2f aPos, sf::Vector2f aSize)
            {
                shape.setPosition(aPos);
                shape.setSize(aSize);
                shape.setFillColor(sf::Color::Yellow);
                shape.setOrigin(aSize.x / 2.0f, aSize.y / 2.0f);
            }

            // x, y: centre or origin of the shape
            float x() { return shape.getPosition().x; }
            float y() { return shape.getPosition().y; }
            // left, right of the shape
            float left() { return x() - shape.getSize().x / 2.0f; }
            float right() { return x() + shape.getSize().x / 2.0f; }
            float top() { return y() - shape.getSize().y / 2.0f; }
            float bottom() { return y() + shape.getSize().y / 2.0f; }
    };

    class Paddle
    {
        private:
            const float paddleVelocity = 6.0f; 
            
            sf::Vector2f windowSize;
            void setWindowSize(sf::Vector2f aWindowSize)
            {
                windowSize.x = aWindowSize.x;
                windowSize.y = aWindowSize.y;
            }

        public: 
            sf::RectangleShape shape; 
            sf::Vector2f size = {80.0f, 20.0f};
            sf::Vector2f velocity {0, 0};

            Paddle(sf::Vector2f aPos, sf::Vector2f aWindowSize)
            {
                shape.setPosition(aPos);
                shape.setSize(size);
                shape.setFillColor(sf::Color::Green);
                shape.setOrigin(size.x / 2.0f, size.y / 2.0f);
                setWindowSize(aWindowSize);
            }

            void update()
            {
                shape.move(velocity);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0)
                {   
                    velocity.x = -paddleVelocity;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < windowSize.x)
                {              
                    velocity.x = paddleVelocity;
                }
                else 
                {
                    velocity.x = 0.0f;
                }

            }

            // x, y: centre or origin of the shape
            float x() { return shape.getPosition().x; }
            float y() { return shape.getPosition().y; }
            // left, right of the shape
            float left() { return x() - size.x / 2.0f; }
            float right() { return x() + size.x / 2.0f; }
            float top() { return y() - size.y / 2.0f; }
            float bottom() { return y() + size.y / 2.0f; }
    };

    class Ball
    {
        private:
            const float ballRadius = 10.0f;
    
            sf::Vector2f windowSize;
            void setWindowSize(sf::Vector2f aWindowSize)
            {
                windowSize.x = aWindowSize.x;
                windowSize.y = aWindowSize.y;
            }

        public: 
            sf::CircleShape shape;
            const float ballVelocity = 8.0f;
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