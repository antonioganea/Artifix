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

        void input();
        void setID( int id );

        void move();
        void attack();
        void ultimate();

    protected:
    private:
        sf::Sprite sprite;
};

#endif // EMERALDO_H
