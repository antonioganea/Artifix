#include "GameState.h"

#include <iostream>

//std::vector<Object*> GameState::m_objects;

GameState::GameState()
{
    //allocate object containers

    std::cout << "GameState created!\n";

    /*
    //DEBUG INFO
    std::cout << std::endl;
    StaticObject * myWall = new StaticObject;
    myWall->setID(5);

    addObject(*myWall);
    */
}

GameState::~GameState()
{
    //dtor
}

/** @brief addObject
  *
  * @todo: document this function
  */
void GameState::addEntity( Entity * entity )
{
    std::cout << "Added object to gamestate!" << std::endl;
    ps_entities.push_back( entity );
}

/** @brief update
  *
  * @todo: document this function
  */
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
/*
    for(it2 = uc.begin(); it2 != uc.end();)
    {
       ...
       if(...)
       {
          it2 = uc.erase(it2);
       }
       else
       {
          ++it2;
       }
       ...
    }
*/
    while ( ps_entities.size() )
    {
        m_entities.push_back ( ps_entities.back() );
        ps_entities.pop_back();
    }
}

/** @brief input
  *
  * @todo: document this function
  */
void GameState::input( const sf::Event & event )
{/*
    for ( std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it )
    {
        (*it)->input(event);
    }*/
}

/** @brief draw
  *
  * @todo: document this function
  */
void GameState::draw()
{
    for ( std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it )
    {
        (*it)->draw();
    }
}
