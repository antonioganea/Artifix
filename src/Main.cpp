#include <SFML/Graphics.hpp>

#include "GameRegistry.h"
#include "Config.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), APP_NAME);
    window.setFramerateLimit(60.f);
    GameRegistry::queueResource("emeraldo.png",ResourceType::Texture);
    GameRegistry::loadResource();

    sf::Texture * tex;
    tex = GameRegistry::getResource("emeraldo.png",ResourceType::Texture).texture;

    sf::Sprite spr;
    spr.setTexture(*tex,true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(spr);
        window.display();
    }

    return 0;
}
