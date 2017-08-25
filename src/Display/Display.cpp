#include "Display.h"

#include <SFML/Graphics.hpp>

#include "Config.h"

sf::RenderWindow * Display::window;
sf::View Display::view;

void Display::init()
{
    Display::window = new sf::RenderWindow( sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), APP_NAME, sf::Style::Fullscreen );
    Display::window->setFramerateLimit(60);
    Display::window->setKeyRepeatEnabled(false);

    Display::view.setSize(WINDOW_WIDTH,WINDOW_HEIGHT);
}

void Display::focusOn( Crystal * crystal ){
    Display::view.setCenter(crystal->getPosition());
    Display::window->setView(Display::view);
}

void Display::resetView(){
    Display::view.setCenter(WINDOW_WIDTH/2.f,WINDOW_HEIGHT/2.f);
    Display::window->setView(Display::view);
}
