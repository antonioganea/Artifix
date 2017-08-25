#include "PickMenu.h"

#include <iostream>

#include "GameRegistry.h"
#include "Display.h"

#include "GuiButton.h"
#include "Config.h"

PickMenu::PickMenu()
{
    std::cout << "Pick Menu created!\n";

    sf::Texture * arenaTexture = GameRegistry::getResource("arena.png",ResourceType::Texture).texture;
    /*
    arena.setSize((sf::Vector2f)arenaTexture->getSize());
    arena.setTexture(arenaTexture);
    arena.setOrigin((sf::Vector2f)arenaTexture->getSize()/2.f);
    arena.setScale(16.f,16.f);
    */
    arena.setSize( sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT) );
    arena.setTexture(arenaTexture);
/*
    GuiButton * button = new GuiButton(5);
    button->setPosition(160,80);
    m_buttons.push_back(button);
*/


    GuiButton * button;

    for ( int i = 0; i < 3; i++ ){
        button = new GuiButton(8+i);
        button->setPosition(760+i*180,540);
        m_buttons.push_back(button);
    }
}

PickMenu::~PickMenu()
{
    //dtor
}

void PickMenu::addEntity( Entity * entity ){
}

void PickMenu::update(float dt){
}

/** @brief input
  *
  * @todo: document this function
  */
void PickMenu::input( const sf::Event & event ){
    for ( std::vector<GuiButton*>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ){
        switch( event.type ){
            case sf::Event::MouseMoved:
                (*it)->checkHover(event.mouseMove);
                break;
            case sf::Event::MouseButtonReleased:
                (*it)->checkClick(event.mouseButton);
                break;
        }
    }
}

void PickMenu::draw()
{
    Display::window->draw(arena);
    for ( std::vector<GuiButton*>::iterator it = m_buttons.begin(); it != m_buttons.end(); it++ ){
        (*it)->draw();
    }
    /*
    for ( std::vector<GuiLabel*>::iterator it = m_labels.begin(); it != m_labels.end(); it++ ){
        (*it)->draw();
    }*/
}
