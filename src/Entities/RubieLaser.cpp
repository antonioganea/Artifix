#include "RubieLaser.h"

#include "GameRegistry.h"
#include "Display.h"

#include "Mechanics.h"
#include "Rubie.h"

#include <stdlib.h>
#include <math.h>

RubieLaser::RubieLaser(){
    sf::Texture * texture = GameRegistry::getResource("laser.png",ResourceType::Texture).texture;
    shape = new sf::RectangleShape( sf::Vector2f(30,8) );
    shape->setTexture(texture,false);
    //shape.setTextureRect(sf::IntRect(sf::Vector2i(16*(animationTimer/5),0),sf::Vector2i(16,16)));
    shape->setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(30,8)));
    shape->setScale(2.f,2.f);
    lifetime = 0;
    //rotationalSpeed = rand()%10+30;
    shape->setOrigin(15,4);
    animationTimer = 0;
}

RubieLaser::RubieLaser( const sf::Vector2f & _position, const sf::Vector2f & _velocity ){
    RubieLaser();

    position = _position;shape->setPosition(position);
    velocity = _velocity;
    lifetime=30;
}

void RubieLaser::reset( const sf::Vector2f & _position, const sf::Vector2f & _velocity ){
    position = _position;
    velocity = _velocity;
    lifetime=30;
    shape->setPosition(position);
    animationTimer = 0;

    float angle = atan2( velocity.y, velocity.x );
    shape->setRotation(angle*180.f/M_PI);


    //rotationalSpeed = rand()%10+30;if ( rand()%2 ) rotationalSpeed*=-1;
}

RubieLaser::~RubieLaser()
{
    //dtor
}

void RubieLaser::draw(){
    shape->setRotation( rotationalSpeed + shape->getRotation() );

    Display::window->draw(*shape);
}

void RubieLaser::update(float dt)
{
    Mechanics::applyFriction(velocity,0.05f);
    position+=velocity;

    if ( animationTimer < 8 ){
        shape->setTextureRect(sf::IntRect(sf::Vector2i(animationTimer/2*30,0),sf::Vector2i(30,8)));
        animationTimer++;
    }

    shape->setPosition(position);

    if (lifetime)
        lifetime--;
}

bool RubieLaser::isDead()
{
    return Mechanics::getSpeed(velocity) < 5.f;
}
