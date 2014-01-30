#ifndef WINDOW_H
#define WINDOW_H

#include <sfml/graphics.hpp>

class Window
{
    public:
        Window(sf::VideoMode, sf::String, int);

        sf::RenderWindow&    getWin();

        virtual ~Window();
    protected:
    private:
        sf::RenderWindow win;

};

#endif // WINDOW_H
