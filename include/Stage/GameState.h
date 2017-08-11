#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "Stage.h"

class GameState : public Stage
{
    public:
        GameState();
        virtual ~GameState();

        void addEntity(Entity * entity);
        void update( float dt );
        void input();
        void draw();

    protected:

    private:
        std::vector<Entity*> m_entities;
        std::vector<Entity*> ps_entities;
};

#endif // GAMESTATE_H
