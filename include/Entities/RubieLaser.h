#ifndef RUBIELASER_H
#define RUBIELASER_H

#include "Entity.h"
#include <SFML/Graphics/RectangleShape.hpp>

class Rubie;

class RubieLaser : public Entity
{
    public:
        RubieLaser();
        RubieLaser( const sf::Vector2f & position, const sf::Vector2f & velocity );
        virtual ~RubieLaser();

        void reset( const sf::Vector2f & position, const sf::Vector2f & velocity );

        void draw();
        void update( float dt );

        bool isDead();

        sf::RectangleShape * shape;
        sf::Vector2f position;
        sf::Vector2f velocity;
        int lifetime;


    protected:
    private:
        float rotationalSpeed;
        int animationTimer;
};

#endif // RUBIELASER_H
