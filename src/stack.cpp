#include "stack.h"

Stack::Stack() :
    gridison( 0 ),
    draftison( 0 )
{
    //ctor
}

Stack::~Stack()
{
    //dtor
}

void Stack::addName(std::string _str)
{
    vNames.push_back( _str );
}

std::vector<std::string> Stack::getNames()
{
    return vNames;
}

void Stack::removeName(std::string)
{

}

void Stack::addCube( std::vector< std::string > _cube )
{
    cube = _cube;
}

std::vector< std::string > Stack::getCube()
{
    return cube;
}
