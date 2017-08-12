#ifndef PARTICLE_H
#define PARTICLE_H

#include "Entity.h"
#include <SFML/Graphics/RectangleShape.hpp>

class Emeraldo;

class Particle : public Entity
{
    public:
        Particle();
        Particle( const sf::Vector2f & position, const sf::Vector2f & velocity );
        virtual ~Particle();

        void reset( const sf::Vector2f & position, const sf::Vector2f & velocity );

        void draw();
        void update( float dt );

        void attack( const sf::Vector2f& target );

        void chase();
        //void setVelocity( const sf::Vector2f& velocity );
        //void setLifeTime( const int& lifetime);

        //void input( const sf::Event & event );
        //void setID( int id );
        bool isDead();
        sf::RectangleShape * shape;
        sf::Vector2f position;
        sf::Vector2f velocity;
        int lifetime;
        bool chasing;

        Emeraldo * caster;
    protected:
    private:
};

#endif // PARTICLE_H
