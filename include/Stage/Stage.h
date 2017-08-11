#ifndef STAGE_H
#define STAGE_H

#include "Entity.h"

class Stage
{
    public:
        //Stage();
        virtual void addEntity ( Entity * entity ) = 0;
        virtual void update( float dt ) = 0;
        virtual void input() = 0;
        virtual void draw() = 0;
    protected:

    private:

};

#endif // STAGE_H
