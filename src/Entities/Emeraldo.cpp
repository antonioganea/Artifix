#include "Emeraldo.h"

#include "GameRegistry.h"
#include "Display.h"

#include "Mechanics.h"
#include "Particle.h"
#include "StageManager.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include <stdlib.h>

#include <iostream>

Emeraldo::Emeraldo(){
    sf::Texture * texture = GameRegistry::getResource("emeraldo.png",ResourceType::Texture).texture;
    sprite.setTexture( *texture, true );
    velocity.x = velocity.y = 0;
    w = a = s = d = false;
}

/*
Emeraldo::~Emeraldo()
{
    //dtor
}
*/

void Emeraldo::draw()
{
    Display::window->draw(sprite);
}

const float acceleration = 0.3f;
const float friction = 0.1f;

void Emeraldo::update(float dt)
{
    Mechanics::applyAcceleration(velocity,d-a,s-w,acceleration);
    Mechanics::applyMaxSpeed(velocity,5.0f);
    Mechanics::applyFriction(velocity,friction);

    sprite.move(velocity.x,velocity.y);
    //disperse();
}

void Emeraldo::disperse(){
    float twist = rand()%10000;
    twist = 31410.f / twist;
    for ( int i = 0; i < 8; i++ ){
        float x = cos ( (float(i)) * M_PI/4.f + twist );
        float y = sin ( (float(i)) * M_PI/4.f + twist );
        Particle * particle = new Particle(sprite.getPosition(),sf::Vector2f(x,y)*15.f);
        StageManager::getStage()->addEntity(particle);
    }
}

void Emeraldo::input( const sf::Event & event )
{
    if ( event.type == sf::Event::LostFocus ){
        w = a = s = d = false;
    }else
    if ( event.type == sf::Event::KeyPressed ){
        switch (event.key.code){
            case sf::Keyboard::A :
                a = true;
                break;
            case sf::Keyboard::D :
                d = true;
                break;
            case sf::Keyboard::W :
                w = true;
                break;
            case sf::Keyboard::S :
                s = true;
                break;
            case sf::Keyboard::G :{
                disperse();
                break;
            }
            default:
                break;
        }
    }
    else if( event.type == sf::Event::KeyReleased ){
        switch (event.key.code){
            case sf::Keyboard::A :
                a = false;
                break;
            case sf::Keyboard::D :
                d = false;
                break;
            case sf::Keyboard::W :
                w = false;
                break;
            case sf::Keyboard::S :
                s = false;
                break;
            default:
                break;
        }
    }
}
/*
void Emeraldo::setID(int id)
{

}
*/

bool Emeraldo::isDead()
{
    return false;
}


void Emeraldo::move()
{

}

void Emeraldo::attack()
{

}

void Emeraldo::ultimate()
{

}
