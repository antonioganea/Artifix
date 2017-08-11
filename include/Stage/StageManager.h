#ifndef STAGEMANAGER_H
#define STAGEMANAGER_H

#include "Stage.h"

class StageManager
{
    public:
        static void init();
        static void setStage( Stage& stage );
        static Stage* getStage();
        static void update( float dt );
        static void input();
        static void draw();
    protected:

    private:
        StageManager();
        static Stage * currentStage;
};

#endif // STAGEMANAGER_H
