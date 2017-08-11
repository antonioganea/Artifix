#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <SFML/Window/Event.hpp>

class Entity
{
    public:
        //Entity();
        //virtual ~Entity();

        virtual void draw() = 0;
        virtual void update( float dt ) = 0;
        virtual bool isDead() = 0;
        //virtual void input( const sf::Event & event ) = 0;

        //virtual void setID( int id ) = 0;
    protected:

    private:
};

#endif // ENTITY_H_INCLUDED
