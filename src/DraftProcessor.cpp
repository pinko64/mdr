#include "DraftProcessor.h"
#include <iostream>

void DraftProcessor::getimgs(  )
{

vTexts.clear();
int X = 0;
for ( int i = 0; i < cube.size() ; i++ )
{

    if ( Fetcher::mTextures.find( cube[ i ] ) != Fetcher::mTextures.end() )
        {
            vShapes[i].setTexture( Fetcher::mTextures[ cube[ i ] ], true );
            //vShapes[i].setFillColor( sf::Color( 255, 255, 255, 255 ) );
        }
        else
        {
         //vShapes[i].setFillColor( sf::Color( 25, 25, 25, 25 ) );
         vShapes[ i ].setTexture( &back );

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
    if ( X == 2 )
        X = 0;
        }

}
}

void DraftProcessor::setBoosters( std::vector<std::string> _cube )
{
    cube = _cube;
    vShapes.clear();
        sf::RectangleShape r1;
    r1.setTexture( &back );
    r1.setSize( sf::Vector2f( 200, 250) );
    for ( int i = 0; i < cube.size(); i++ )
    vShapes.push_back( r1 );

    arrange();

}


DraftProcessor::DraftProcessor(  )
{
    font.loadFromFile( "font.ttf" );
    current = 9;
    back.loadFromFile( "back.jpg" );
    back.setSmooth( 1 );
    back.setRepeated( 1 );
    //back = fet.Fetch( "balance" );


    //ctor
}

DraftProcessor::~DraftProcessor()
{
    //dtor
}

void DraftProcessor::arrange( )
{
vRects.clear();

int Off = 0;
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
    if (i == 4)
        {
            Y += vShapes[i].getSize().y ;
            X = 0;
        }
         if (i == 9)
        {
            Y += vShapes[i].getSize().y ;
            X = 0;
        }








}




}





