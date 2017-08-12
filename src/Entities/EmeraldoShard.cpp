#include "EmeraldoShard.h"

#include "GameRegistry.h"
#include "Display.h"

#include "Mechanics.h"
#include "Emeraldo.h"

//sf::RectangleShape * shape;
//Emeraldo * caster;

EmeraldoShard::EmeraldoShard(){
    sf::Texture * texture = GameRegistry::getResource("shard.png",ResourceType::Texture).texture;
    shape = new sf::RectangleShape( (sf::Vector2f)texture->getSize() );
    shape->setTexture(texture,false);
    lifetime = 0;
    chasing = false;
}

EmeraldoShard::EmeraldoShard( const sf::Vector2f & _position, const sf::Vector2f & _velocity ){
    EmeraldoShard();

    position = _position;shape->setPosition(position);
    velocity = _velocity;
    lifetime=30;
}

void EmeraldoShard::reset( const sf::Vector2f & _position, const sf::Vector2f & _velocity ){
    position = _position;
    velocity = _velocity;
    lifetime=30;
    shape->setPosition(position);
    chasing = false;
}

EmeraldoShard::~EmeraldoShard()
{
    //dtor
}

void EmeraldoShard::draw(){
    Display::window->draw(*shape);
}

void EmeraldoShard::update(float dt)
{
    Mechanics::applyFriction(velocity,0.1f);
    position+=velocity;
    shape->setPosition(position);

    if (chasing)
        chase();
    if ( lifetime ){
        lifetime--;
        if ( !lifetime ){
            chase();
        }
    }
}

void EmeraldoShard::chase(){
    if ( Mechanics::checkEpsilon(target->position,position,0.5f) ){
        chasing = false;
        velocity *= 0.f;
        return;
    }
    velocity = target->position-position;
    Mechanics::applyMaxSpeed(velocity,15.f);
    chasing = true;
}

bool EmeraldoShard::isDead()
{
    return !chasing && !lifetime;
}
