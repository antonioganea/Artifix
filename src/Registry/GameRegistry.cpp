#include "GameRegistry.h"

#include <string>
#include <iostream>

std::map<std::string, ResourcePtr> GameRegistry::m_resources;
std::stack<ResourceCommand> GameRegistry::m_commands;

void GameRegistry::init(){
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
    GameRegistry::queueResource("playbtn-sheet.png",ResourceType::Texture);
    GameRegistry::queueResource("optionsbtn-sheet.png",ResourceType::Texture);
    GameRegistry::queueResource("creditsbtn-sheet.png",ResourceType::Texture);
    GameRegistry::queueResource("exitbtn-sheet.png",ResourceType::Texture);
    GameRegistry::queueResource("backbtn-sheet.png",ResourceType::Texture);
    GameRegistry::queueResource("picktxt.png", ResourceType::Texture);
    GameRegistry::queueResource("arena.png", ResourceType::Texture);
    GameRegistry::queueResource("dpcomic.ttf",ResourceType::Font);
    GameRegistry::queueResource("connectbtn-sheet.png", ResourceType::Texture);
    GameRegistry::queueResource("readybtn-sheet.png", ResourceType::Texture);
    GameRegistry::queueResource("emeraldo-pick.png", ResourceType::Texture);
    GameRegistry::queueResource("rubie-pick.png", ResourceType::Texture);
    GameRegistry::queueResource("sapheer-pick.png", ResourceType::Texture);
    while (!GameRegistry::loadResource()){}
}

bool GameRegistry::queueResource( const std::string& filePath, const ResourceType& type  )
{
    ResourceCommand command;
    command.filePath = filePath;
    command.type = type;
    m_commands.push( command );
    std::cout << "Queued resource : "<< filePath << std::endl;
    return true;
}

std::string composeFullPath( const std::string& filePath, const ResourceType& type ){
    std::string fullPath;
    switch ( type ){
    case ResourceType::Texture:
        fullPath = "data/textures/" + filePath;
        break;
    case ResourceType::Font:
        fullPath = "data/fonts/" + filePath;
        break;
    case ResourceType::SoundBuffer:
        fullPath = "data/sounds/" + filePath;
        break;
    }
    std::cout << "Composed fullPath : "<< fullPath << std::endl;
    return fullPath;
}

ResourcePtr GameRegistry::getResource( const std::string& filePath, const ResourceType& type ){
    std::string fullPath = composeFullPath( filePath, type );
    std::cout << "Returning resource : "<< fullPath << std::endl;
    return m_resources.find(fullPath)->second;//use full path
}

bool GameRegistry::loadResource()
{
    if ( m_commands.size() )
    {
        ResourceType type = m_commands.top().type;
        std::string fullPath = composeFullPath( m_commands.top().filePath, type );

        ResourcePtr res;

        switch ( type ){
            case ResourceType::Texture :{
                sf::Texture * texture = new sf::Texture;
                texture->loadFromFile(fullPath);
                res.texture = texture;
                std::cout << "Loading texture : "<< fullPath << std::endl;
                std::cout << "BOOP : X : " << texture->getSize().x << "  Y : " << texture->getSize().y << std::endl;
                break;
            }
            case ResourceType::Font :{
                sf::Font * font = new sf::Font;
                font->loadFromFile(fullPath);
                res.font = font;
                std::cout << "Loading font : "<< fullPath << std::endl;
                break;
            }
            case ResourceType::SoundBuffer :{
                sf::SoundBuffer * soundBuffer = new sf::SoundBuffer;
                soundBuffer->loadFromFile(fullPath);
                res.soundBuffer = soundBuffer;
                std::cout << "Loading sound : "<< fullPath << std::endl;
                break;
            }
        };

        m_commands.pop();

        m_resources.insert(std::pair<std::string,ResourcePtr>(fullPath, res));

        return false;
    }
    else
        return true;
}
