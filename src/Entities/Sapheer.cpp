#include "Sapheer.h"

#include "GameRegistry.h"
#include "Display.h"

#include "Mechanics.h"
#include "StageManager.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include <stdlib.h>

#include <iostream>

const float Sapheer::acceleration = 0.3f;
const float Sapheer::friction = 0.1f;
//const int Sapheer::abilityCooldown = 60;

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

    texture = GameRegistry::getResource("shard_sapheer.png",ResourceType::Texture).texture;
    shootParticles = new Particle[16];
    for ( int i = 0; i < 16; i++ ) shootParticles[i].setTexture(texture);

    velocity.x = velocity.y = 0;
    w = a = s = d = false;
    cooldown = 0;
    animationTimer = 0;
    shieldTimer = 20;
}

void Sapheer::draw(){
    for ( int i = 0; i < 16; i++ )
        if ( !shootParticles[i].isDead() )
            shootParticles[i].draw();

    if ( shieldTimer != 20 )
        Display::window->draw(*shield);

    Display::window->draw(sprite);
}

sf::Vector2f Sapheer::getPosition(){
    return sprite.getPosition();
}

void Sapheer::update(float dt){
    for ( int i = 0; i < 16; i++ )
        shootParticles[i].update(dt);

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

void Sapheer::shoot(){
    if ( Mechanics::getSpeed(velocity) < 2.f )
        return;
    for ( int i = 0; i < 16; i++ ){
        if ( shootParticles[i].isDead() ){
            shootParticles[i].reset(sprite.getPosition(),velocity*15.f,30);
            break;
        }
    }
}

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
            case sf::Keyboard::G :
                throwShield();
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
