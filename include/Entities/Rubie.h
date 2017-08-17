#ifndef RUBIE_H
#define RUBIE_H

#include "Crystal.h"
#include "RubieLaser.h"
#include <SFML/Graphics/Sprite.hpp>

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
        void shoot();
        RubieLaser * lasers;
        sf::Sprite sprite;
        sf::Vector2f velocity;
        int w,a,s,d;
        int cooldown;
        int animationTimer;

};

#endif // RUBIE_H
