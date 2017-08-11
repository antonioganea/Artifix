#ifndef CHAMPION_H
#define CHAMPION_H

#include "Entity.h"
#include <SFML/Window/Event.hpp>

class Champion : public Entity
{
    public:
        //Champion();
        //virtual ~Champion();

        virtual void draw() = 0;
        virtual void update( float dt ) = 0;

        virtual void input( const sf::Event & event ) = 0;
        virtual void setID( int id ) = 0;

        virtual void move() = 0;
        virtual void attack() = 0;
        virtual void ultimate() = 0;

    protected:
    private:
};

#endif // CHAMPION_H
