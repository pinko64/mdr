#ifndef BUTTON_H
#define BUTTON_H
#include <sfml/graphics.hpp>
#include <string>

#include <iostream>

class Button
{
    public:
        Button( int, int, int, int, std::string _str);
        Button();


        void     setPosition(int,int);
        void     setSize(int,int);


        sf::IntRect  getRect();
        sf::Vector2f getSize();


        sf::Text    text;
        sf::Font    font;

        void     draw(sf::RenderWindow&);
        bool     press();
        virtual ~Button();
    protected:
    private:
        bool isDown;

    std::string  title;
sf::RectangleShape shape;
    sf::IntRect    rect;
   sf::Clock  clock;


};

#endif // BUTTON_H
