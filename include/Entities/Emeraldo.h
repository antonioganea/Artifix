#ifndef EMERALDO_H
#define EMERALDO_H

#include "Champion.h"
#include <SFML/Graphics/Sprite.hpp>

class Emeraldo : public Champion{
    public:
        Emeraldo();
        //virtual ~Emeraldo();
        void draw();
        void update( float dt );

        void input( const sf::Event & event );
        void setID( int id );

        void move();
        void attack();
        void ultimate();

    protected:
    private:
        sf::Sprite sprite;
        int vx, vy;
};

#endif // EMERALDO_H
