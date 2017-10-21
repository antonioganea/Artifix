#include "GameState.h"

#include <iostream>

#include "SyncManager.h"
#include "GameRegistry.h"
#include "Display.h"

GameState::GameState()
{
    //allocate object containers

    std::cout << "GameState created!\n";

    sf::Texture * arenaTexture = GameRegistry::getResource("icepattern.png",ResourceType::Texture).texture;
    arena.setSize((sf::Vector2f)arenaTexture->getSize());
    arena.setTexture(arenaTexture);
    arena.setOrigin((sf::Vector2f)arenaTexture->getSize()/2.f);
    arena.setScale(16.f,16.f);

    circle.setRadius(300);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(5);
    circle.setOrigin(500,500);
}

GameState::~GameState()
{
    //dtor
}

void GameState::addEntity( Entity * entity )
{
    std::cout << "Added object to gamestate!" << std::endl;
    ps_entities.push_back( entity );
}

void GameState::update(float dt)
{
    for ( std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end();)
    {
        (*it)->update(dt);
        if ( (*it)->isDead() ){
            std::cout<<"ERASED ENTITY"<<std::endl;
            delete (*it);
            it = m_entities.erase(it);
        }
        else
            ++it;
    }

    while ( ps_entities.size() )
    {
        m_entities.push_back ( ps_entities.back() );
        ps_entities.pop_back();
    }
}

void GameState::input( const sf::Event & event )
{
    SyncManager::input(event);
}

void GameState::draw()
{
    if ( SyncManager::myPlayerID != -1 )
        Display::focusOn(SyncManager::crystals[SyncManager::myPlayerID]);
    Display::window->draw(arena);
    Display::window->draw(circle);
    for ( std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it )
    {
        (*it)->draw();
    }
}
