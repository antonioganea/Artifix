#include <SFML/Graphics.hpp>

#include "Display.h"
#include "GameRegistry.h"
#include "StageManager.h"

#include "Emeraldo.h"
#include "Rubie.h"
#include "Sapheer.h"
#include "Particle.h"

#include <time.h>
#include <stdlib.h>

int main()
{
    srand(time(NULL));

    GameRegistry::queueResource("emeraldo.png",ResourceType::Texture);
    GameRegistry::queueResource("shard_emeraldo.png",ResourceType::Texture);
    GameRegistry::queueResource("shard.png",ResourceType::Texture);
    GameRegistry::queueResource("rubie.png",ResourceType::Texture);
    GameRegistry::queueResource("shard_rubie.png",ResourceType::Texture);
    GameRegistry::queueResource("laser.png",ResourceType::Texture);
    GameRegistry::queueResource("sapheer.png",ResourceType::Texture);
    GameRegistry::queueResource("shard_sapheer.png",ResourceType::Texture);
    GameRegistry::queueResource("walls.png",ResourceType::Texture);
    while (!GameRegistry::loadResource()){}

    Display::init();

    StageManager::init();

    Stage * stage = StageManager::getStage();

    //Emeraldo * champion = new Emeraldo();
    Rubie * champion = new Rubie();
    //Sapheer * champion = new Sapheer();

    stage->addEntity(champion);

    while (Display::window->isOpen())
    {
        sf::Event event;
        while (Display::window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Display::window->close();
            if (event.type == sf::Event::KeyPressed ){
            }
            champion->input(event);
        }

        Display::window->clear();
        StageManager::update(10.f);
        StageManager::draw();
        Display::window->display();
    }

    return 0;
}
