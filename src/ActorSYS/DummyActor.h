#ifndef DUMMYACTOR_H
#define DUMMYACTOR_H

#include "Actor.h"

class DummyActor : public Actor
{
    public:
        DummyActor();
        virtual ~DummyActor();


        void update()
        {

        }
        void tick(float delta)
        {

        }
        void GameStart()
        {

        }

    protected:

    private:
};

#endif // DUMMYACTOR_H