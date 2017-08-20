#ifndef EMERALDO_H
#define EMERALDO_H

#include "Crystal.h"
#include <SFML/Graphics/Sprite.hpp>
#include "EmeraldoShard.h"
#include "Particle.h"

class Emeraldo : public Crystal{
    public:
        Emeraldo();
        //virtual ~Emeraldo();
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
        const static int lookup[9];
        const static int abilityCooldown;

        sf::Sprite sprite;

        EmeraldoShard * dispersionParticles;
        void disperse();

        Particle * shootParticles;
        void shoot();

        int w,a,s,d;
        sf::Vector2f velocity;

        bool inDispersion, visible;
        int cooldown, animationTimer, dispersionParticleNo;
};

#endif // EMERALDO_H
