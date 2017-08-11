#include "Emeraldo.h"

#include "GameRegistry.h"
#include "Display.h"

#include <iostream>

Emeraldo::Emeraldo(){
    sf::Texture * texture = GameRegistry::getResource("emeraldo.png",ResourceType::Texture).texture;
    sprite.setTexture( *texture, true );
    vx = vy = 0; // velocities set to 0
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

void Emeraldo::update(float dt)
{
    sprite.move(vx,vy);
}


void Emeraldo::input( const sf::Event & event )
{
    if ( event.type == sf::Event::KeyPressed ){
        switch (event.key.code){
            case sf::Keyboard::A :
                vx = -5;
                break;
            case sf::Keyboard::D :
                vx = 5;
                break;
            case sf::Keyboard::W :
                vy = -5;
                break;
            case sf::Keyboard::S :
                vy = 5;
                break;
            default:
                break;
        }
    }
    else if( event.type == sf::Event::KeyReleased ){
        switch (event.key.code){
            case sf::Keyboard::A :
                vx = 0;
                break;
            case sf::Keyboard::D :
                vx = 0;
                break;
            case sf::Keyboard::W :
                vy = 0;
                break;
            case sf::Keyboard::S :
                vy = 0;
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
