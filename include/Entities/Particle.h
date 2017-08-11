#ifndef PARTICLE_H
#define PARTICLE_H

#include "Entity.h"
#include <SFML/Graphics/RectangleShape.hpp>


class Particle : public Entity
{
    public:
        Particle( const sf::Vector2f & position, const sf::Vector2f & velocity );
        virtual ~Particle();

        void draw();
        void update( float dt );
        //void input( const sf::Event & event );
        //void setID( int id );
        bool isDead();
    protected:
    private:
        sf::RectangleShape * shape;
        sf::Vector2f position;
        sf::Vector2f velocity;
        int lifetime;
};

#endif // PARTICLE_H
