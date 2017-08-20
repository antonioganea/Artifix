#include "Emeraldo.h"

#include "GameRegistry.h"
#include "Display.h"

#include "Mechanics.h"
#include "EmeraldoShard.h"
#include "StageManager.h"

#define _USE_MATH_DEFINES
#include "math.h"

#include <stdlib.h>
#include <iostream>

const float Emeraldo::acceleration = 0.3f;
const float Emeraldo::friction = 0.1f;
const int Emeraldo::lookup[9] = {5,4,3,6,-1,2,7,0,1};//proud of this
const int Emeraldo::abilityCooldown = 60;

Emeraldo::Emeraldo(){
    sf::Texture * texture = GameRegistry::getResource("emeraldo.png",ResourceType::Texture).texture;
    sprite.setTexture( *texture, false );
    sprite.setScale( 2.f, 2.f );
    sprite.setOrigin( 8.f, 8.f );
    sprite.setTextureRect( sf::IntRect( sf::Vector2i(0,0), sf::Vector2i(16,16) ) );

    dispersionParticles = new EmeraldoShard[8];
    for ( int i = 0; i < 8; i++ ) dispersionParticles[i].target = dispersionParticles;
    inDispersion = false;

    texture = GameRegistry::getResource("shard_emeraldo.png",ResourceType::Texture).texture;
    shootParticles = new Particle[16];
    for ( int i = 0; i < 16; i++ ) shootParticles[i].setTexture(texture);

    w = a = s = d = false;
    visible = true;

    velocity.x = velocity.y = 0;
    cooldown = 0;
    animationTimer = 0;
    dispersionParticleNo = 0;
}

void Emeraldo::draw(){
    for ( int i = 0; i < 16; i++ )
        if ( !shootParticles[i].isDead() )
            shootParticles[i].draw();
    if( inDispersion )
        for ( int i = 0; i < 8; i++ )
            dispersionParticles[i].draw();
    else
        Display::window->draw(sprite);
}

sf::Vector2f Emeraldo::getPosition(){
    return sprite.getPosition();
}

void Emeraldo::update(float dt){
    for ( int i = 0; i < 8; i++ )
        dispersionParticles[i].update(dt);

    for ( int i = 0; i < 16; i++ )
        shootParticles[i].update(dt);

    int count = 0;
    for ( int i = 0; i < 8; i++ )
        if (dispersionParticles[i].isDead())
            count++;

    if ( count==8 && inDispersion ){
        inDispersion = false;
        sprite.setPosition(dispersionParticles[0].position);
        velocity *= 0.0f;
    }

/*
    std::cout << dispersionParticleNo << "    ";
    for ( int i = 0; i < 8; i++ )
        std::cout << dispersionParticles[i].isDead() << " ";
    std::cout << std::endl;
*/

    Mechanics::applyAcceleration(velocity,d-a,s-w,acceleration);
    Mechanics::applyMaxSpeed(velocity,5.0f);
    Mechanics::applyFriction(velocity,friction);

    animationTimer++;
    if ( animationTimer >= 40 )
        animationTimer = 0;

    sprite.setTextureRect(sf::IntRect(sf::Vector2i(16*(animationTimer/5),0),sf::Vector2i(16,16)));

    sprite.move(velocity.x,velocity.y);

    if (cooldown) cooldown--;
}

void Emeraldo::disperse(){
    if ( !cooldown ){
        dispersionParticleNo = lookup[ (d-a+1)*3 + s-w+1 ];
        if ( dispersionParticleNo != -1 ){
            for ( int i = 0; i < 8; i++ ){
                float x = cos ( (float(i)) * M_PI/4.f );
                float y = sin ( (float(i)) * M_PI/4.f );
                dispersionParticles[i].reset(sprite.getPosition(),sf::Vector2f(x,y)*20.f);
                dispersionParticles[i].target = dispersionParticles+dispersionParticleNo;
            }
        cooldown = abilityCooldown;
        inDispersion = true;
        }
    }
}

void Emeraldo::shoot(){
    if ( Mechanics::getSpeed(velocity) < 2.f )
        return;
    for ( int i = 0; i < 16; i++ ){
        if ( shootParticles[i].isDead() ){
            shootParticles[i].reset(sprite.getPosition(),velocity*15.f,30);
            break;
        }
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
            case sf::Keyboard::G :
                disperse();
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

bool Emeraldo::isDead(){
    return false;
}


void Emeraldo::move(){

}

void Emeraldo::attack(){

}

void Emeraldo::ultimate(){

}
