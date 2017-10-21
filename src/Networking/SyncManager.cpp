#include "SyncManager.h"

#include "StageManager.h"
#include "Emeraldo.h"
#include "Rubie.h"
#include "Sapheer.h"

#include <string.h>
#include <iostream>

sf::TcpSocket SyncManager::socket;
char * SyncManager::packageBuffer;
Crystal * SyncManager::crystals[MAX_PLAYERS];
char * SyncManager::options;
bool SyncManager::players[MAX_PLAYERS];
int SyncManager::myPlayerID;

void SyncManager::init(){
    SyncManager::packageBuffer = new char[128];
    SyncManager::options = new char[128];
    for ( int i = 0; i < MAX_PLAYERS; i++ )
        SyncManager::players[i] = false;
    std::cout << "SyncManager Initialized!" << std::endl;
    SyncManager::myPlayerID = -1;
}

void SyncManager::connectToServer( const sf::IpAddress& address ){
    std::cout << "Attempting to connect to server.. on port 4474" << std::endl;
    sf::Socket::Status status = SyncManager::socket.connect( address, 4474, sf::Time::Zero );
    if ( status == sf::Socket::Status::Done )
        std::cout << "Successfully connected to server!" << std::endl;
    else
        std::cout << "Failed to connect to server!" << std::endl;
}


//*********************************SENDING PART***************************************
void SyncManager::sendCrystalType ( int type ){
    SyncManager::packageBuffer[0] = 1;//package type
    SyncManager::packageBuffer[1] = type;
    SyncManager::socket.send(SyncManager::packageBuffer,2);
    std::cout << "Sent crystal type successfully!" << std::endl;
}

void SyncManager::sendPosition(const sf::Vector2f& position){
    sf::Int32 x = position.x;
    sf::Int32 y = position.y;
    *SyncManager::packageBuffer = 2; // package code ( position = 2 )
    memcpy(SyncManager::packageBuffer+1,&x,sizeof(sf::Int32));
    memcpy(SyncManager::packageBuffer+sizeof(sf::Int32)+1,&y,sizeof(sf::Int32));
    SyncManager::socket.send(SyncManager::packageBuffer,sizeof(sf::Int32)*2+1);
}

void SyncManager::sendShoot( const sf::Vector2f& velocity ){
    float x = velocity.x;
    float y = velocity.y;
    *SyncManager::packageBuffer = 3; // package code ( attack = 3 )
    memcpy(SyncManager::packageBuffer+1,&x,sizeof(float));
    memcpy(SyncManager::packageBuffer+sizeof(float)+1,&y,sizeof(float));
    SyncManager::socket.send(SyncManager::packageBuffer,sizeof(float)*2+1);
}

void SyncManager::sendUltimate(){
    SyncManager::packageBuffer[0] = 4; // package code ( ultimate = 4 / no payload )
    SyncManager::socket.send(SyncManager::packageBuffer,1);
}

void SyncManager::sendUltimate( char options ){
    SyncManager::packageBuffer[0] = 5; // package code ( ultimate = 5 / 1 byte payload )
    SyncManager::packageBuffer[1] = options;
    SyncManager::socket.send(SyncManager::packageBuffer,2);
}

void SyncManager::sendUltimate( float options ){
    SyncManager::packageBuffer[0] = 6; // package code ( ultimate = 6 / 4 byte payload )
    ((float*)(SyncManager::packageBuffer+1))[0] = options;
    SyncManager::socket.send(SyncManager::packageBuffer,5);
}

void SyncManager::sendLaserCollision( int player ){
    SyncManager::packageBuffer[0] = 7; // package code ( laserCollision / 4 byte payload )
    memcpy(SyncManager::packageBuffer+1,&player,4);
    SyncManager::socket.send(SyncManager::packageBuffer,5);
}

void SyncManager::sendShieldCollision( int player ){
    SyncManager::packageBuffer[0] = 8; // package code ( shield collision / 4 byte payload )
    memcpy(SyncManager::packageBuffer+1,&player,4);
    SyncManager::socket.send(SyncManager::packageBuffer,5);
}

void SyncManager::sendParticleCollision( int player ){
    SyncManager::packageBuffer[0] = 9; // package code ( particle collision / 4 byte payload )
    memcpy(SyncManager::packageBuffer+1,&player,4);
    SyncManager::socket.send(SyncManager::packageBuffer,5);
}

//**************************************************************************************

//**********************************RECEIVING PART**************************************

void SyncManager::receivePackets(){
    sf::Socket::Status status;
    std::size_t received;

    //TODO : find a way to write this without toggling setBlocking() twice every frame
    SyncManager::socket.setBlocking(false); // TODO : GET RID OF THIS
    status = SyncManager::socket.receive(SyncManager::packageBuffer,128,received);
    if ( status == sf::Socket::Status::Done ){
        SyncManager::parseBuffer( received );

        std::cout << "RECEIVED A PACKET " << received << " bytes" << std::endl;
        for ( int i = 0; i < received; i++ ){
            std::cout << (int)(SyncManager::packageBuffer[i]) << " ";
        }std::cout << std::endl;

    }
    SyncManager::socket.setBlocking(true); // TODO : GET RID OF THIS
}

void SyncManager::parseBuffer( std::size_t received ){
    char * cursor = SyncManager::packageBuffer;
    int player;

    std::cout << "Received " << received << " bytes." << std::endl;

    while ( cursor - SyncManager::packageBuffer < received )
    {
        player = *cursor;
        cursor++;
        switch( *cursor ){ // Packet Code

            case 1:{ // Crystal Type
                std::cout << "Type 1 - crystal type" << std::endl;
                cursor++;
                SyncManager::players[player] = true;
                switch( *cursor ){ // Crystal Type Number
                    case 1:{
                        Emeraldo * emeraldo = new Emeraldo();
                        emeraldo->setSyncer(player);
                        StageManager::gameState->addEntity( emeraldo );
                        SyncManager::crystals[player] = emeraldo;
                        std::cout << "CREATED EMERALDO" << std::endl;
                        break;
                    }
                    case 2:{
                        Rubie * rubie = new Rubie();
                        rubie->setSyncer(player);
                        StageManager::gameState->addEntity( rubie );
                        SyncManager::crystals[player] = rubie;
                        std::cout << "CREATED RUBIE" << std::endl;
                        break;
                    }
                    case 3:{
                        Sapheer * sapheer = new Sapheer();
                        sapheer->setSyncer(player);
                        StageManager::gameState->addEntity( sapheer );
                        SyncManager::crystals[player] = sapheer;
                        std::cout << "CREATED SAPHEER" << std::endl;
                        break;
                    }
                }
                if ( player == SyncManager::myPlayerID ){
                    SyncManager::crystals[player]->setSyncable(true);
                }
                cursor++;
                break;
            }
            case 2:{ // Position package
                //std::cout << "Type 2 - position type" << std::endl;
                cursor++;
                sf::Int32 x,y;
                memcpy(&x,cursor,4);
                memcpy(&y,cursor+4,4);
                if ( SyncManager::players[player] )
                    SyncManager::crystals[player]->setPosition(sf::Vector2f(x,y));
                cursor += 8;
                break;
            }
            case 3:{ // Basic attack package
                std::cout << "Type 3 - basic attack --RECEIVED " << received << std::endl;
                cursor++;
                memcpy(SyncManager::options, cursor, 8 );
                SyncManager::crystals[player]->attack();
                cursor += 8;
                break;
            }
            case 4:{ // Ultimate package ( no options )
                std::cout << "Type 4 - ultimate ( no options )" << std::endl;
                cursor++;
                //memcpy(SyncManager::options,cursor,1);
                SyncManager::crystals[player]->ultimate();
                break;
            }
            case 5:{ // Ultimate package ( 1 byte )
                std::cout << "Type 5 - ultimate ( 1 byte )" << std::endl;
                cursor++;
                memcpy(SyncManager::options,cursor,1);
                SyncManager::crystals[player]->ultimate();
                cursor++;
                break;
            }
            case 6:{ // Ultimate package ( 4 bytes )
                std::cout << "Type 6 - ultimate ( 4 bytes )" << std::endl;
                cursor++;
                memcpy(SyncManager::options,cursor,4);
                SyncManager::crystals[player]->ultimate();
                cursor+=4;
                break;
            }
            case 10:{
                std::cout << "Type 10 - Health Points" << std::endl;
                cursor++;
                int hp;
                memcpy(&hp,cursor,4);
                //TODO
                cursor+=4;
                break;
            }
            case 11:{
                std::cout << "Type 11 - Disconnected player" << std::endl;
                cursor++;
                SyncManager::crystals[player]->markDead();
                SyncManager::crystals[player] = nullptr;
                SyncManager::players[player] = false;
                std::cout << "CALLED DEAD MARKUP" << std::endl;
                break;
            }
            case 12:{
                std::cout << "Type 12 - Received player ID" << std::endl;
                cursor++;
                SyncManager::myPlayerID = player;
                SyncManager::players[player] = true;
                break;
            }
            case 13:{ // Push Crystal
                std::cout << "Type 13 - Push crystal type" << std::endl;
                cursor++;
                float x,y;
                memcpy(&x,cursor,4);
                memcpy(&y,cursor+4,4);
                if ( SyncManager::players[SyncManager::myPlayerID] )
                    SyncManager::crystals[myPlayerID]->pushCrystal(sf::Vector2f(x,y));
                cursor += 8;
                break;
            }
            default:{
                cursor++;
            }
            //...
        }
    }
}
//**************************************************************************************

void SyncManager::input( sf::Event event ){
    if ( SyncManager::myPlayerID != -1 ){
        SyncManager::crystals[SyncManager::myPlayerID]->input(event);
    }
}
