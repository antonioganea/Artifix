#include "Emeraldo.h"

#include "GameRegistry.h"
#include "Display.h"

#include "Mechanics.h"

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

void Emeraldo::setID(int id)
{

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
