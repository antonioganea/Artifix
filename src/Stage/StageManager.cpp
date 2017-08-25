#include "StageManager.h"

#include "GameState.h"
#include "Display.h"

#include <iostream>

Stage * StageManager::currentStage;

GameState * StageManager::gameState;
MainMenu * StageManager::mainMenu;
CreditsMenu * StageManager::creditsMenu;
ConnectMenu * StageManager::connectMenu;
PickMenu * StageManager::pickMenu;

std::stack<Stage*> StageManager::m_stages;

/** @brief init
  *
  * @todo: document this function
  */
void StageManager::init()
{
    StageManager::gameState = new GameState;
    StageManager::mainMenu = new MainMenu;
    StageManager::creditsMenu = new CreditsMenu;
    StageManager::connectMenu = new ConnectMenu;
    StageManager::pickMenu = new PickMenu;

    StageManager::currentStage = mainMenu;
    m_stages.push(currentStage);
}

/** @brief setStage
  *
  * @todo: document this function
  */
void StageManager::pushStage( Stage * stage ){
    if ( stage != m_stages.top() ){
        m_stages.push(stage);
        Display::resetView();
    }
}

void StageManager::popStage(){
    if ( m_stages.size() > 1 ){
        m_stages.pop();
        Display::resetView();
    }
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

/** This is the first "StageManager" function to run in the loop */
void StageManager::updateCurrentStage(){
    currentStage = m_stages.top();
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
