#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

class Entity
{
    public:
        //Entity();
        //virtual ~Entity();

        virtual void draw() = 0;
        virtual void update( float dt ) = 0;
        virtual void input() = 0;
        virtual void setID( int id ) = 0;
    protected:

    private:
};

#endif // ENTITY_H_INCLUDED
