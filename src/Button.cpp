#include "Button.h"

Button::Button()
{
    //ctor
}

Button::Button( int _x, int _y, int _xx, int _yy, std::string _str )
{

    shape.setPosition( sf::Vector2f( _x, _y ) );
    shape.setSize( sf::Vector2f( _xx, _yy ) );
    shape.setFillColor( sf::Color( 50,50,50,155 ) );
    shape.setOutlineThickness( 4 );
    shape.setOutlineColor( sf::Color( 75, 75, 75, 200) );

    if (!font.loadFromFile( "font.ttf" ))
    {
        std::cout << "Could not load the font" << std::endl;
    };

    text.setFont( font );
    text.setCharacterSize( 45 );
    text.setString( _str );
    text.setStyle( sf::Text::Bold );
    text.setColor( sf::Color::White );
    text.setPosition( shape.getPosition().x + 5, shape.getPosition().y + 5 );

    rect = sf::IntRect( _x, _y, _xx, _yy );


}


Button::~Button()
{
    //dtor
}

sf::Vector2f Button::getSize()
{
    return shape.getSize();
}

void Button::draw(sf::RenderWindow &_win)
{

    text.setColor( sf::Color( text.getColor().r + 1, text.getColor().g - 1, text.getColor().b, text.getColor().a ) );
    text.setFont( font );
    _win.draw( shape );
    _win.draw( text );

}


sf::IntRect Button::getRect()
{
    return rect;
}
