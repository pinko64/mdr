#include "People.h"

People::People( Stack &_stack ) :
stack(_stack)
{
        font.loadFromFile( "font.ttf" );
        //vppl.clear();
        txt.setFont( font );
        txtdef.setFont( font );
        txtdef.setString( "Connected:" );
        txtdef.setScale( 1, 0.75 );
        txtdef.setStyle( sf::Text::Style::Bold );

}

People::~People()
{
    //dtor
}

void People::draw(sf::RenderWindow& win)
{

shape.setPosition( 0, win.getSize().y - 25 );
shape.setSize( sf::Vector2f( win.getSize().x, 25 ) );
shape.setFillColor( sf::Color::Black );
win.draw( shape );

txtdef.setPosition( 0, win.getSize().y - 25 );
win.draw( txtdef );

int tx = 0;




tx += txtdef.getGlobalBounds().width + 5;


for ( int i = 0; i < vTexts.size(); i++ )
{
    if ( i == stack.whosTurn )
        vTexts[ i ].setColor( sf::Color::Green );
    else
        vTexts[ i ].setColor( sf::Color::Blue );
}

for (auto x : vTexts)
{
    win.draw( x );
}

}

void People::addppl( std::string str )
{
//vppl.push_back(str);
sf::Text txt;
txt.setString( str );
txt.setFont( font );
//txt.setColor( sf::Color::Blue );
txt.setStyle( sf::Text::Style::Bold );

if ( vTexts.size() > 0 )
txt.setPosition( sf::Vector2f( vTexts.back().getPosition().x + vTexts.back().getGlobalBounds().width + 15 , txtdef.getPosition().y - 4 ) );

else
    txt.setPosition( txtdef.getPosition().x + txtdef.getGlobalBounds().width + 5, txtdef.getPosition().y - 4 );


vTexts.push_back( txt );
}


void People::addppl( std::vector< std::string > str )
{
//vppl.push_back(str);
vTexts.clear();

for ( int i = 0; i < str.size(); i++ )
{
            sf::Text txt;
            if ( vTexts.size() > 0 )
                txt.setPosition( sf::Vector2f( vTexts.back().getPosition().x + vTexts.back().getGlobalBounds().width + 15 , txtdef.getPosition().y - 4 ) );
            else
                txt.setPosition( txtdef.getPosition().x + txtdef.getGlobalBounds().width + 5, txtdef.getPosition().y - 4 );

            txt.setFont( font );
            txt.setColor( sf::Color::Blue );
          //  txt.setPosition( 250, 350);
        //    txt.setCharacterSize( 50 );
            txt.setStyle( sf::Text::Style::Bold );
            txt.setString( str [ i ] );

                vTexts.push_back( txt );
}

}




std::vector< sf::Text > People::getppl()
{
return vTexts;
}
