#include "Emeraldo.h"

#include "GameRegistry.h"
#include "Display.h"

Emeraldo::Emeraldo(){
    sf::Texture * texture = GameRegistry::getResource("emeraldo.png",ResourceType::Texture).texture;
    sprite.setTexture( *texture, true );
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

}


void Emeraldo::input()
{

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
