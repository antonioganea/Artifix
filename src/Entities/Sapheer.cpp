#include "Sapheer.h"

#include "GameRegistry.h"
#include "Display.h"

#include "Mechanics.h"
#include "StageManager.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include <stdlib.h>

#include <iostream>

Sapheer::Sapheer(){
    sf::Texture * texture = GameRegistry::getResource("sapheer.png",ResourceType::Texture).texture;
    sprite.setTexture( *texture, false );
    sprite.setScale(2.f,2.f);
    //sprite.setOrigin(8.f,8.f);
    sprite.setOrigin(8.f,8.f);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(16,16)));

    texture = GameRegistry::getResource("walls.png",ResourceType::Texture).texture;
    shield = new sf::RectangleShape( sf::Vector2f(256,256) );
    shield->setTexture(texture,true);
    shield->setOrigin(128.f,128.f);
    shield->setScale(2.f,2.f);

    velocity.x = velocity.y = 0;
    w = a = s = d = false;
    cooldown = 0;
    animationTimer = 0;
    shieldTimer = 20;
}

void Sapheer::draw(){
    if ( shieldTimer != 20 )
        Display::window->draw(*shield);

    Display::window->draw(sprite);
}

sf::Vector2f Sapheer::getPosition(){
    return sprite.getPosition();
}

const float acceleration = 0.3f;
const float friction = 0.1f;

void Sapheer::update(float dt)
{
    if ( Mechanics::getSpeed(velocity) < 5.0f ){
        Mechanics::applyAcceleration(velocity,d-a,s-w,acceleration);
        Mechanics::applyMaxSpeed(velocity,5.0f);
    }
    Mechanics::applyFriction(velocity,friction);

    animationTimer++;
    if ( animationTimer >= 25 )
        animationTimer = 0;

    if ( shieldTimer && shieldTimer < 20 )
        shieldTimer++;

    //std::cout << "Timer : " << shieldTimer << std::endl;

    sprite.setTextureRect(sf::IntRect(sf::Vector2i(16*(animationTimer/5),0),sf::Vector2i(16,16)));
    shield->setTextureRect(sf::IntRect(sf::Vector2i(256*(shieldTimer/5),0),sf::Vector2i(256,256)));

    sprite.move(velocity.x,velocity.y);
    shield->setPosition(sprite.getPosition());

    if (cooldown) cooldown--;
}
/*
void Sapheer::shoot(){
    //if (!( d-a or s-w )) // if no direction is available
        //return;

    if ( Mechanics::getSpeed(velocity) < 1.f )
        return;

    float angle = atan2( velocity.y, velocity.x );

    velocity.x = cos(angle)*30.f;
    velocity.y = sin(angle)*30.f;

    float count = 0;
    for ( int i = 0; i < MAX_LASERS; i++ ){
        if ( lasers[i].isDead() ){
            float x = cos ( count*M_PI/14.f - M_PI*5.f/4.f + angle );
            float y = sin ( count*M_PI/14.f - M_PI*5.f/4.f + angle );
            lasers[i].reset(sprite.getPosition(),sf::Vector2f(x,y)*30.f);
            count++;
            if ( count == 8 )
                break;
        }
    }
}*/

void Sapheer::throwShield(){
    if ( cooldown )
        return;
    shieldTimer = 1;
    cooldown = 30;
}

void Sapheer::input( const sf::Event & event )
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
                throwShield();
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

bool Sapheer::isDead()
{
    return false;
}


void Sapheer::move()
{

}

void Sapheer::attack()
{

}

void Sapheer::ultimate()
{

}
