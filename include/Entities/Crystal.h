#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "Entity.h"
#include <SFML/Window/Event.hpp>

class Crystal : public Entity
{
    public:
        //Crystal();
        //virtual ~Crystal();

        virtual void draw() = 0;
        virtual void update( float dt ) = 0;
        virtual bool isDead() = 0;

        virtual void input( const sf::Event & event ) = 0;
        //virtual void setID( int id ) = 0;

        virtual void move() = 0;
        virtual void attack() = 0;
        virtual void ultimate() = 0;

    protected:
    private:
};

#endif // CRYSTAL_H
