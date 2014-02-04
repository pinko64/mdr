#include "Gridprocessor.h"
#include <iostream>


void Gridprocessor::getimgs(  )
{

vTexts.clear();
int X = 0;
for ( int i = 0; i < 9; i++ )
{
        size_t swp;
        swp = cube[i].find( "Æ" );
        if ( swp!=std::string::npos )
        {
     //       v[i].replace( swp-1, 3, 1, ' ' );
            cube[i][swp] = 'a';
            cube[i].insert( swp+1, "e" );
        }

    if ( Fetcher::mTextures.find( cube[ i ] ) != Fetcher::mTextures.end() )
        {
            vShapes[i].setTexture( &*Fetcher::mTextures[ cube[ i ] ], true );
         //std::cout << cube[i] << std::endl;
            //vShapes[i].setFillColor( sf::Color( 255, 255, 255, 255 ) );
        }
        else
        {
         //vShapes[i].setFillColor( sf::Color( 25, 25, 25, 25 ) );
         vShapes[ i ].setTexture( &back );
        }
//        vShapes[ i ].set
        //vShapes[i].setTextureRect( sf::IntRect( 200, 200 ,
          //                                  vShapes[i].getTexture()->getSize().x, vShapes[i].getTexture()->getSize().y ) );

    sf::Text txt;
    txt.setFont( font );
    txt.setStyle( sf::Text::Style::Bold );
    txt.setString( cube[ i ] );
    txt.setColor( sf::Color( 255, 255, 255, 255 ) );
    txt.setCharacterSize( 25 );
    txt.setPosition(
                    vShapes[ i ].getPosition().x,
                    vShapes[ i ].getPosition().y + X * 15
                     );
    vTexts.push_back( txt );
    X++;
    if ( X == 3 )
        X = 0;
}



}

void Gridprocessor::setCube( std::vector<std::string> _cube )
{
    cube = _cube;
        for ( auto &x : cube )
    {
        std::replace( x.begin(), x.end(), '_', ' ');
    }
}


Gridprocessor::Gridprocessor(  )
{
    font.loadFromFile( "font.ttf" );
    current = 9;
    back.loadFromFile( "back.jpg" );
    back.setSmooth( 1 );
    back.setRepeated( 1 );
    //back = fet.Fetch( "balance" );

    sf::RectangleShape r1;
    r1.setTexture( &back );
    r1.setSize( sf::Vector2f( 200, 250) );
    for ( int i = 0; i < 9; i++ )
    vShapes.push_back( r1 );

    arrange();


    //ctor
}

Gridprocessor::~Gridprocessor()
{
    //dtor
}

void Gridprocessor::arrange( )
{
vRects.clear();

int Y = 0;
int X = 0;
for ( int i = 0; i < vShapes.size(); i++ )
{

    vShapes[i].setPosition( sf::Vector2f(X*vShapes[i].getSize().x ,   Y  ) );
    sf::IntRect Rect = sf::IntRect(
                                   vShapes[i].getPosition().x,
                                   vShapes[i].getPosition().y,
                                   vShapes[i].getSize().x,
                                   vShapes[i].getSize().y
                                   );
                                   vRects.push_back(Rect);


    X++;
    if (i == 2)
        {
            Y += vShapes[i].getSize().y ;
            X = 0;
        }
         if (i == 5)
        {
            Y += vShapes[i].getSize().y ;
            X = 0;
        }








}




}





