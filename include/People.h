#ifndef PEOPLE_H
#define PEOPLE_H

#include <vector>
#include <string>
#include <map>
#include <sfml/graphics.hpp>

#include <iostream>
#include "stack.h"

class People
{
    public:
        People(Stack &_stack);


        Stack                    &stack;
        void                     addppl(std::string);
        std::vector< sf::Text > getppl();
        std::vector<sf::Text>    vTexts;
        void                     addppl( std::vector< std::string > str );

        void draw(sf::RenderWindow&);

        virtual ~People();
    protected:
    private:
        std::vector<std::string> vppl;
        sf::RectangleShape     shape;
        sf::Text                 txt;
        sf::Text               txtdef;
        sf::Font                font;

};

#endif // PEOPLE_H
