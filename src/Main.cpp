#include <SFML/Graphics.hpp>

#include "Display.h"
#include "GameRegistry.h"
#include "StageManager.h"

#include "SyncManager.h"

#include "Emeraldo.h"
#include "Rubie.h"
#include "Sapheer.h"
#include "Particle.h"

#include <time.h>
#include <stdlib.h>

int main(){
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
    GameRegistry::queueResource("icepattern.png",ResourceType::Texture);
    while (!GameRegistry::loadResource()){}

    Display::init();

    StageManager::init();

    Stage * stage = StageManager::getStage();

    //Emeraldo * champion = new Emeraldo();
    //Rubie * champion = new Rubie();
    Sapheer * champion = new Sapheer();

    champion->setSyncable(true);
    stage->addEntity(champion);

    SyncManager::myCrystal = champion;

    SyncManager::init();
    SyncManager::connectToServer( sf::IpAddress(127,0,0,1) );

    sf::Texture * arenaTexture = GameRegistry::getResource("icepattern.png",ResourceType::Texture).texture;
    sf::RectangleShape arena;
    arena.setSize((sf::Vector2f)arenaTexture->getSize());
    arena.setTexture(arenaTexture);
    arena.setOrigin((sf::Vector2f)arenaTexture->getSize()/2.f);
    arena.setScale(16.f,16.f);

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

        SyncManager::receivePackets();
        StageManager::update(10.f);

        Display::window->clear();
        Display::window->draw(arena);
        StageManager::draw();
        Display::window->display();
    }

    return 0;
}
