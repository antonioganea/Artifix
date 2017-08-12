#ifndef EMERALDO_H
#define EMERALDO_H

#include "Champion.h"
#include <SFML/Graphics/Sprite.hpp>
#include "Particle.h"

class Emeraldo : public Champion{
    public:
        Emeraldo();
        //virtual ~Emeraldo();
        void draw();
        void update( float dt );

        bool isDead();

        void input( const sf::Event & event );
        //void setID( int id );

        void move();
        void attack();
        void ultimate();

    protected:
    private:
        Particle * dispersionParticles;
        void disperse();
        sf::Sprite sprite;
        sf::Vector2f velocity;
        int w,a,s,d;
        bool inDispersion;
        bool visible;
};

#endif // EMERALDO_H
