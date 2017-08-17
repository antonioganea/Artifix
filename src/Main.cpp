#include <SFML/Graphics.hpp>

#include "Display.h"
#include "GameRegistry.h"
#include "StageManager.h"

#include "Emeraldo.h"
#include "Rubie.h"
#include "Particle.h"

#include <time.h>
#include <stdlib.h>

int main()
{
    srand(time(NULL));

    GameRegistry::queueResource("emeraldo.png",ResourceType::Texture);
    GameRegistry::queueResource("shard.png",ResourceType::Texture);
    GameRegistry::queueResource("food.png",ResourceType::Texture);
    GameRegistry::queueResource("rubie.png",ResourceType::Texture);
    GameRegistry::queueResource("laser.png",ResourceType::Texture);
    while (!GameRegistry::loadResource()){}

    Display::init();

    StageManager::init();

    Stage * stage = StageManager::getStage();

    //Emeraldo * emeraldo = new Emeraldo();
    Rubie * rubie = new Rubie();

    stage->addEntity(rubie);

    while (Display::window->isOpen())
    {
        sf::Event event;
        while (Display::window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Display::window->close();
            if (event.type == sf::Event::KeyPressed ){
            }
            rubie->input(event);
        }

        Display::window->clear();
        StageManager::update(10.f);
        StageManager::draw();
        Display::window->display();
    }

    return 0;
}
