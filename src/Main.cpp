#include <SFML/Graphics.hpp>

#include "Display.h"
#include "GameRegistry.h"

int main()
{
    GameRegistry::queueResource("emeraldo.png",ResourceType::Texture);
    GameRegistry::loadResource();

    sf::Texture * tex;
    tex = GameRegistry::getResource("emeraldo.png",ResourceType::Texture).texture;

    sf::Sprite spr;
    spr.setTexture(*tex,true);

    Display::init();

    while (Display::window->isOpen())
    {
        sf::Event event;
        while (Display::window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Display::window->close();
        }

        Display::window->clear();
        Display::window->draw(spr);
        Display::window->display();
    }

    return 0;
}
