#include "Emeraldo.h"

#include "GameRegistry.h"
#include "Display.h"

#include <iostream>

Emeraldo::Emeraldo(){
    sf::Texture * texture = GameRegistry::getResource("emeraldo.png",ResourceType::Texture).texture;
    sprite.setTexture( *texture, true );
    vx = vy = 0; // velocities set to 0
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
    vx += ((float)(d-a))*acceleration;
    vy += ((float)(s-w))*acceleration;


    //Speed limits
    if ( vx > 10 )
        vx = 10;
    else if ( vx < -10 )
        vx = -10;

    if ( vy > 10 )
        vy = 10;
    else if ( vy < -10 )
        vy = -10;

    //Friction
    if ( vx > 0 ){
        vx -= friction;
        if ( vx < 0 )
            vx = 0;
    }

    if ( vx < 0 ){
        vx += friction;
        if ( vx > 0 )
            vx = 0;
    }

    if ( vy > 0 ){
        vy -= friction;
        if ( vy < 0 )
            vy = 0;
    }

    if ( vy < 0 ){
        vy += friction;
        if ( vy > 0 )
            vy = 0;
    }

    sprite.move(vx,vy);
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
