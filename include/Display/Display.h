#ifndef DISPLAY_H
#define DISPLAY_H

#include <SFML/Graphics/RenderWindow.hpp>

class Display
{
    public:
        static void init();
        static sf::RenderWindow * window;
    protected:

    private:
        Display();
};

#endif // DISPLAY_H
