#include "StageManager.h"

#include "GameState.h"

#include <iostream>

Stage * StageManager::currentStage;

/*
StageManager::StageManager()
{
    //ctor
}
*/

/** @brief init
  *
  * @todo: document this function
  */
void StageManager::init()
{
    GameState * gameState = new GameState;
    StageManager::currentStage = gameState;
}

/** @brief setStage
  *
  * @todo: document this function
  */
void StageManager::setStage(Stage& stage)
{
    //queue stage
}

/** @brief getStage
  *
  * @todo: document this function
  */
Stage* StageManager::getStage()
{
    return StageManager::currentStage;
}


/** @brief update
  *
  * @todo: document this function
  */
void StageManager::update(float dt)
{
    //std::cout << "MEEEEEEOWWWWW";
    StageManager::currentStage->update(dt);
}

/** @brief input
  *
  * @todo: document this function
  */
void StageManager::input( const sf::Event & event )
{
    currentStage->input( event );
}

/** @brief draw
  *
  * @todo: document this function
  */
void StageManager::draw()
{
    currentStage->draw();
}

/** @brief StageManager
  *
  * @todo: document this function
  */
StageManager::StageManager()
{

}
