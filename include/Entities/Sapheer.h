#ifndef SAPHEER_H
#define SAPHEER_H

#include "Crystal.h"
#include "RubieLaser.h"
#include <SFML/Graphics/Sprite.hpp>
#include "Particle.h"

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
        const static float acceleration;
        const static float friction;
        //const static int abilityCooldown;

        sf::Sprite sprite;

        sf::RectangleShape * shield;
        void throwShield();

        Particle * shootParticles;
        void shoot();

        sf::Vector2f velocity;
        int w,a,s,d;
        int cooldown, animationTimer, shieldTimer;
};

#endif // SAPHEER_H
