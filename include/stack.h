#ifndef STACK_H
#define STACK_H

#include <sfml/system.hpp>
#include <vector>
#include <string>

struct destroyed
{
    destroyed(){};
    sf::Int32 x;
    sf::Int32 y;
    destroyed(sf::Int32 _x, sf::Int32 _y){x = _x; y = _y;};
};

class Stack
{
    public:
        Stack();

        std::vector<std::string>  getNames();
        void  addCube( std::vector<std::string> );
        std::vector<std::string>  getCube();
        void      addName( std::string );
        void      removeName( std::string );
        std::vector<int> Row;




        bool      gridison;
        bool      draftison;

        std::vector<destroyed> vDestroyed;

        int        pplREADY;
        int        ID;

        int       whosTurn;

        virtual ~Stack();
    protected:
    private:
        std::vector<std::string> vNames;
        std::vector<std::string>  cube;
};

#endif // STACK_H
