#include "Grid.h"

Grid::Grid( sf::RenderWindow& _rWin, Server &_srv, Client &_client, Stack &_stack , People &_ppl) :
    rWin(_rWin),
    srv(_srv),
    ppl(_ppl),
    isRunning(1),
    Current(0),
    State(0),
    myTurn(0),
    client(_client),
    stack(_stack),
    checknumber( 0 ),
    End( 0 )
    {

    sfFont.loadFromFile( "font.ttf" );
    txtEnd.setString( "Draft has ended. Check your name.dec file." );
    txtEnd.setFont( sfFont );
    txtEnd.setCharacterSize( 30 );

    }

void Grid::checkRow()
{
    if ( !stack.Row.empty() )
    {
        std::vector< int > ints;
        for ( int i = 0; i < 3; i++ )
        {
            ints.push_back( stack.Row[i] );
        }
        stack.Row.clear();
    Shoot( ints );

    }


}



void Grid::preShoot( std::vector<int> &_ints )
{
if ( shootClock.getElapsedTime().asSeconds() > 0.5 )
{



sf::Packet packet;
packet.clear();
//packet << 110 << _ints[0] << _ints[1] <<  _ints[2];
sf::Int32 id = 110;
packet << id << _ints[0] << _ints[1] <<  _ints[2];;
client.Send(packet);







for ( int i = 0; i < _ints.size(); i++ )
{
    deckout.push_back( cubeUnedited[ _ints[ i ] ] );
    std::cout << cubeUnedited.back() << " pushed" << std::endl;
}




//dwriter.write( deckout, ppl.getppl()[ stack.ID ].getString() );
shootClock.restart();
/*
sf::Packet packet;
sf::Int32 id = 12;
packet << 12;
client.Send(packet);
*/
}

}



void Grid::Shoot(std::vector<int> &_ints)
{

///std::cout << "cards size = " << rCards.size() << std::endl;
///std::cout << _ints[0] << _ints[1] <<  _ints[2]  << std::endl;


for ( int i = 0; i < _ints.size(); i++ )
{
    //alldecks[ stack.whosTurn ].push_back( gp.cube[ _ints[ i ] ] );
    alldecks[ stack.whosTurn ].push_back( cubeUnedited[ _ints[ i ] ] );
}


    dwriter.write( alldecks[ stack.whosTurn ], ppl.vTexts[ stack.whosTurn ].getString() );




for (int i = 0; i < 3; i++)
{


    if (gp.current + 3 > cube.size())
    {
        std::cout << "WARNINGWARNING NO MORE CARDS" << std::endl;

        break;
        txtEnd.setString( "Draft has ended. No more cards to fill..." );
        End = 1;
    }


    std::swap(gp.cube[ _ints[ i ] ], gp.cube[ gp.current ] );
    std::swap( cubeUnedited[ _ints[ i ] ], cubeUnedited[ gp.current ] );
    gp.current++;

}




shootclock.restart();
nextTurn();

checknumber += 3;
if ( checknumber >= 45 * ppl.vTexts.size() )
    End = 1;
    std::cout << "End = " << End << std::endl;


}



Grid::~Grid()
{
    //dtor
}


std::vector<int> Grid::Friends(int _int, bool _alt)
{
if (!_alt){
if (_int == 0 || _int == 1 || _int == 2)
    {
        std::vector<int> ints;
        ints.push_back(0);ints.push_back(1);ints.push_back(2);
        return ints;




    }
if (_int == 3 || _int == 4 || _int == 5)
    {
        std::vector<int> ints;
        ints.push_back(3);ints.push_back(4);ints.push_back(5);
        return ints;
    }

if (_int == 6 || _int == 7 || _int == 8)
{
        std::vector<int>  ints;
        ints.push_back(6);ints.push_back(7);ints.push_back(8);
        return ints;
}

}



else if (_alt){
if (_int == 0 || _int == 3 || _int == 6)
    {
        std::vector<int> ints;
        ints.push_back(0);ints.push_back(3);ints.push_back(6);
        return ints;

    }
if (_int == 1 || _int == 4 || _int == 7)
    {
        std::vector<int> ints;
        ints.push_back(1);ints.push_back(4);ints.push_back(7);
        return ints;
    }
if (_int == 2 || _int == 5 || _int == 8)
{
        std::vector<int>  ints;
        ints.push_back(2);ints.push_back(5);ints.push_back(8);
        return ints;
}
}}







void Grid::Loop(  ) {






CubeReader cr;
std::vector< std::string > vOutput = stack.getCube();
cubeUnedited = vOutput;
cube = cr( vOutput );
Fetcher f( cube );

for ( auto& x : cube )
{
    size_t c = x.find( ";" );
    x.erase( c, std::string::npos );
    std::cout << x << std::endl;
}

//gp.setCube( stack.getCube() );
gp.setCube( cube );



std::vector< std::string > vst;
for ( int i = 0; i < ppl.vTexts.size(); i++ )
alldecks.push_back( vst );






while (rWin.isOpen())
{




sf::Event event;
                while (rWin.pollEvent(event))
                    {
                if (event.type == sf::Event::Closed)
                {
                    rWin.close();isRunning=0; exit(0);
                }

                    }

        if (!End)
            {

        gp.getimgs(  );



checkRow();

for (int i = 0; i < gp.vRects.size(); i++)
{

    if (
        gp.vRects[i].contains
        (
        sf::Mouse::getPosition( rWin ) )
        && !sf::Keyboard::isKeyPressed( sf::Keyboard::LAlt )
        && stack.whosTurn == stack.ID
        )
    {
        std::vector<int> Ints;
            //d::cout << i ;
            Ints = Friends(i,0);

        for (int j = 0; j < Ints.size(); j++)
        {


            gp.vShapes[ Ints[ j ] ].setFillColor(sf::Color::Red);


        }

            if ( sf::Keyboard::isKeyPressed( sf::Keyboard::LControl ) )
            {
                std::cout << std::endl << gp.cube[ i ] << std::endl;
            }

            if (
                sf::Keyboard::isKeyPressed(sf::Keyboard::Space)
                && shootclock.getElapsedTime().asSeconds() > 0.5
                )

                {

                    preShoot(Ints);break;

                }
                    if (i == 8 || i == 7 || i == 6) break;
                    i = Ints.back() + 1;

    }

gp.vShapes[i].setFillColor(sf::Color(255,255,255,255));
}







for (int i = 0; i < gp.vRects.size(); i++)
{


    if (
        gp.vRects[i].contains( sf::Mouse::getPosition( rWin ) )
        && sf::Keyboard::isKeyPressed( sf::Keyboard::LAlt )
        && stack.whosTurn == stack.ID
        )
    {
        std::vector<int> Ints;

            Ints = Friends(i,1);

        for (int j = 0; j < Ints.size(); j++)
        {
            gp.vShapes[ Ints[ j ] ].setFillColor(sf::Color::Red);

        }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {

                    preShoot(Ints);break;

                }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
            {
                for (int ii = 0; ii < Ints.size(); ii++)
                {
                ///std::cout << rCards[Ints.at(ii)].Name << std::endl;
                }
             }
        i = Ints.back() + 1;

    }

//gp.vShapes[i].setFillColor(sf::Color(255,255,255,255));
}



if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
{
for (int i = 0; i < gp.vRects.size(); i++)
{
    if ( gp.vRects[ i ].contains( sf::Mouse::getPosition( rWin ) ) )
    {
        zoom.setTexture( gp.vShapes[ i ].getTexture(), true );
        zoom.setSize(sf::Vector2f(500,700));
        zoomclock.restart();
        }

}


}

            }





        rWin.clear( );

        //if (zoomclock.getElapsedTime().asSeconds() < 0.02)rWin.draw(zoom);

        if ( !End )
            {


        for ( auto x : gp.vShapes )
            rWin.draw( x );
            for ( auto x : gp.vTexts )
                rWin.draw( x );
        //rWin.draw( gp.)
        ppl.draw( rWin );
        if (zoomclock.getElapsedTime().asSeconds() < 0.02)rWin.draw(zoom);
        }
        if ( End )
            rWin.draw( txtEnd );

        rWin.display();

}
}




 void Grid::Start() ///only the server may start
{


if (State != 1){
    State = 1;
std::cout << "Starts.";
//int x = rand() % (connecteds.ppl.size() - 1) + 0;
//srand(time(NULL));

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

std::mt19937 mt(seed);
}}


void Grid::nextTurn()
{

        stack.whosTurn++;
       if ( stack.whosTurn > ppl.getppl().size() - 1)
        {
            stack.whosTurn = 0;
        }
        std::cout << "sz o : " << ppl.getppl().size();

}

