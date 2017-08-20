#ifndef RUBIE_H
#define RUBIE_H

#include "Crystal.h"
#include "RubieLaser.h"
#include <SFML/Graphics/Sprite.hpp>
#include "Particle.h"

class Rubie : public Crystal{
    public:
        Rubie();
        //virtual ~Rubie();
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
        const static int abilityCooldown;

        RubieLaser * lasers;
        void jetAway();

        Particle * shootParticles;
        void shoot();

        sf::Sprite sprite;
        sf::Vector2f velocity;
        int w,a,s,d;
        int cooldown;
        int animationTimer;

};

#endif // RUBIE_H
