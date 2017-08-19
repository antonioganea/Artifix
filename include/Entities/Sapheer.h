#ifndef SAPHEER_H
#define SAPHEER_H

#include "Crystal.h"
#include "RubieLaser.h"
#include <SFML/Graphics/Sprite.hpp>

class Sapheer : public Crystal{
    public:
        Sapheer();
        //virtual ~Sapheer();
        void draw();
        void update( float dt );

        bool isDead();

        void input( const sf::Event & event );

        sf::Vector2f getPosition();

        void move();
        void attack();
        void ultimate();
    protected:
    private:
        void throwShield();
        sf::Sprite sprite;
        sf::RectangleShape * shield;
        sf::Vector2f velocity;
        int w,a,s,d;
        int cooldown, animationTimer, shieldTimer;
};

#endif // SAPHEER_H
