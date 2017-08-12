#include "Particle.h"

#include "GameRegistry.h"
#include "Display.h"

#include "Mechanics.h"
#include "Emeraldo.h"

//sf::RectangleShape * shape;
//Emeraldo * caster;

Particle::Particle(){
    sf::Texture * texture = GameRegistry::getResource("shard.png",ResourceType::Texture).texture;
    shape = new sf::RectangleShape( (sf::Vector2f)texture->getSize() );
    shape->setTexture(texture,false);
    lifetime = 0;
    chasing = false;
}

Particle::Particle( const sf::Vector2f & _position, const sf::Vector2f & _velocity ){
    position = _position;
    velocity = _velocity;
    lifetime=30;
    sf::Texture * texture = GameRegistry::getResource("shard.png",ResourceType::Texture).texture;
    shape = new sf::RectangleShape( (sf::Vector2f)texture->getSize() );
    shape->setTexture(texture,false);
    shape->setPosition(position);
    chasing = false;
}

void Particle::reset( const sf::Vector2f & _position, const sf::Vector2f & _velocity ){
    position = _position;
    velocity = _velocity;
    lifetime=30;
    shape->setPosition(position);
    chasing = false;
}

void Particle::attack( const sf::Vector2f& target ){
    velocity = (target-position)*0.15f;
}
/*
void Particle::setVelocity( const sf::Vector2f& _velocity ){
    velocity = _velocity;
}

void Particle::setLifeTime( const int& _lifetime){
    lifetime = _lifetime;
}
*/
Particle::~Particle()
{
    //dtor
}

void Particle::draw(){
    Display::window->draw(*shape);
}

void Particle::update(float dt)
{
    Mechanics::applyFriction(velocity,0.1f);
    position+=velocity;
    shape->setPosition(position);
    if (lifetime)
        lifetime--;
    else
        chase();
}

void Particle::chase(){
    if ( Mechanics::checkEpsilon(caster->getPosition(),position,0.5f) ){
        chasing = false;
        return;
    }
    velocity = caster->getPosition()-position;
    Mechanics::applyMaxSpeed(velocity,15.f);
    chasing = true;
}


/*
void Particle::input(const sf::Event& event)
{

}

void Particle::setID(int id)
{

}
*/
bool Particle::isDead()
{
    return !chasing && !lifetime;
}
