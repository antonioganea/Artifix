#include "Display.h"

#include <SFML/Graphics.hpp>

#include "Config.h"

sf::RenderWindow * Display::window;

/** @brief init
  *
  * @todo: document this function
  */
void Display::init()
{
    Display::window = new sf::RenderWindow( sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), APP_NAME );
    Display::window->setFramerateLimit(60);
}
