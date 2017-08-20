#include "Rubie.h"

#include "GameRegistry.h"
#include "Display.h"

#include "Mechanics.h"
#include "StageManager.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include <stdlib.h>

#include <iostream>

#define MAX_LASERS 16

const float Rubie::acceleration = 0.3f;
const float Rubie::friction = 0.1f;
const int Rubie::abilityCooldown = 60;

Rubie::Rubie(){
    sf::Texture * texture = GameRegistry::getResource("rubie.png",ResourceType::Texture).texture;
    sprite.setTexture( *texture, false );
    sprite.setScale(2.f,2.f);
    sprite.setOrigin(8.f,8.f);
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(16,16)));

    texture = GameRegistry::getResource("shard_rubie.png",ResourceType::Texture).texture;
    shootParticles = new Particle[16];
    for ( int i = 0; i < 16; i++ ) shootParticles[i].setTexture(texture);

    velocity.x = velocity.y = 0;
    w = a = s = d = false;
    cooldown = 0;
    animationTimer = 0;

    lasers = new RubieLaser[MAX_LASERS];
}

void Rubie::draw()
{
    for ( int i = 0; i < 16; i++ )
        if ( !shootParticles[i].isDead() )
            shootParticles[i].draw();
    for ( int i = 0; i < MAX_LASERS; i++ ){
        if ( !lasers[i].isDead() ){
            lasers[i].draw();
        }
    }
    Display::window->draw(sprite);
}

sf::Vector2f Rubie::getPosition()
{
    return sprite.getPosition();
}

void Rubie::update(float dt){
    for ( int i = 0; i < 16; i++ )
        shootParticles[i].update(dt);

    for ( int i = 0; i < MAX_LASERS; i++ ){
        if ( !lasers[i].isDead() ){
            lasers[i].update( dt );
        }
    }
    if ( Mechanics::getSpeed(velocity) < 5.0f ){
        Mechanics::applyAcceleration(velocity,d-a,s-w,acceleration);
        Mechanics::applyMaxSpeed(velocity,5.0f);
    }
    Mechanics::applyFriction(velocity,friction);

    animationTimer++;
    if ( animationTimer >= 25 )
        animationTimer = 0;

    sprite.setTextureRect(sf::IntRect(sf::Vector2i(16*(animationTimer/5),0),sf::Vector2i(16,16)));

    sprite.move(velocity.x,velocity.y);

    if (cooldown) cooldown--;
}

void Rubie::jetAway(){
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
}

void Rubie::shoot(){
    if ( Mechanics::getSpeed(velocity) < 2.f )
        return;
    for ( int i = 0; i < 16; i++ ){
        if ( shootParticles[i].isDead() ){
            shootParticles[i].reset(sprite.getPosition(),velocity*15.f,30);
            break;
        }
    }
}

void Rubie::input( const sf::Event & event )
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
            case sf::Keyboard::G :
                jetAway();
                break;
            case sf::Keyboard::F :
                shoot();
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

bool Rubie::isDead()
{
    return false;
}


void Rubie::move()
{

}

void Rubie::attack()
{

}

void Rubie::ultimate()
{

}
