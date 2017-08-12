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
    dispersionParticles = new Particle[8];
    inDispersion = false;
    visible = true;
}

/*
Emeraldo::~Emeraldo()
{
    //dtor
}
*/

void Emeraldo::draw()
{
    if( inDispersion ){
        for ( int i = 0; i < 8; i++ ){
            dispersionParticles[i].draw();
        }
    }
    else{
        Display::window->draw(sprite);
    }
}

const float acceleration = 0.3f;
const float friction = 0.1f;

int lookup[9] = {5,4,3,6,-1,2,7,0,1};//proud of this

void Emeraldo::update(float dt)
{
    if( !dispersionParticles->isDead()){
            for ( int i = 0; i < 8; i++ ){
                dispersionParticles[i].update(dt);
            }
    }
    else{
        if ( inDispersion ){
            int dispersionParticleNo = lookup[ (d-a+1)*3 + s-w+1 ];
            if ( dispersionParticleNo != -1 ){
                inDispersion = false;
                sprite.setPosition(dispersionParticles[dispersionParticleNo].position);
                velocity *= 0.0f;
            }

            /*
            for ( int i = 0; i < 8; i++ ){

                //dispersionParticles[i].setLifeTime(30);
                //dispersionParticles[i].attack(sprite.getPosition());
            }*/
        }
    }

    Mechanics::applyAcceleration(velocity,d-a,s-w,acceleration);
    Mechanics::applyMaxSpeed(velocity,5.0f);
    Mechanics::applyFriction(velocity,friction);

    sprite.move(velocity.x,velocity.y);
    //disperse();
}

void Emeraldo::disperse(){
    if( inDispersion )
        return;
    inDispersion = true;
    //float twist = rand()%10000;
    //twist = 31410.f / twist;
    for ( int i = 0; i < 8; i++ ){
        float x = cos ( (float(i)) * M_PI/4.f ); //+ twist );
        float y = sin ( (float(i)) * M_PI/4.f ); //+ twist );
        dispersionParticles[i].reset(sprite.getPosition(),sf::Vector2f(x,y)*20.f);
        //StageManager::getStage()->addEntity(dispersionParticles+i);
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
