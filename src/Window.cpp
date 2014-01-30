#include "Window.h"

Window::Window( sf::VideoMode _vm, sf::String _title, int _refresh ) :
    win( _vm, _title ,sf::Style::Close )
{
    win.setFramerateLimit( 60 );

    //ctor
}

Window::~Window()
{
    //dtor
}


sf::RenderWindow& Window::getWin()
{
    return win;
}
