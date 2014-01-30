#include "Manager.h"

	static inline std::string int2Str(int x)
	{
		std::stringstream type;
		type << x;
		return type.str();
	}


Manager::Manager( sf::VideoMode _vm, std::string _title, int _refresh ) :
    Win( _vm, _title, _refresh ),
    win( Win.getWin() ),
    state( 0 ),
    srv( conf.getIncomingPort() ),
    ppl( stack ),
    clt( conf.getIpToConnect(), conf.getPortToConnect(), this, stack, ppl, conf.getName() ),
    grid( Win.getWin() , srv, clt, stack, ppl )
    {
    ///clt.setname( "Bob the dog" );
    cube = cubereader.read( "cube.dec" );
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
     srand(seed);
    std::random_shuffle(cube.begin(), cube.end());

//std::unique_ptr< Draft > pDraft( new Draft( win, srv, clt, ppl, cube ) );
//pDraft->Loop();

    //ctor
///btnhost( (int) win.getSize().x - 200, 0, 100, 100 )

    btnhost = Button(win.getSize().x - 200, 100, 100, 100, "Host" );
    btnconnect = Button(win.getSize().x - 200, 300, 100, 100, "Normal" );
    btngrid = Button(win.getSize().x - 200, 500, 100, 100, "Grid" );

    //cube stuff

    font.loadFromFile( "font.ttf" );
    text.setFont( font );
    text.setColor( sf::Color::Red );
    std::string tmp = "Cube has ";
    tmp += int2Str( cube.size() );
    tmp += " cards.";
    text.setString( tmp );

    std::string h = "Host";
    //create



    loop();

}

Manager::~Manager()
{
    //dtor
}
void Manager::test()
{

    for (int i = 0; i < 2500; i++)
        std::cout << "test";


}


void Manager::loop()
{

std::random_device rdev;
std::mt19937 rgen( rdev() );



while ( state != 10 )
    {

        if (stack.gridison)
            state = 1;
        if ( state == 1) //grid draft
        {
            grid.Loop(cube);
        }
        if (stack.draftison)
            state = 1;
        if ( state == 1)
        {
            std::unique_ptr< Draft > pDraft( new Draft( win, srv, clt, ppl, cube, stack ) );
            pDraft->Loop();
            state = 10;
        }




        sf::Event event;
            while ( win.pollEvent( event ) )
            {
                if ( event.type == sf::Event::Closed )
                    {
                        state = 10;
                        if ( srv.ServerActive )
                        {
                            srv.ServerActive = 0;
                            srv.threadServer.join();
                        }
                        if ( clt.ClientActive )
                        {
                            clt.ClientActive = 0;
                            clt.threadClient.join();
                        }
                        win.close();
                    }



if ( btnhost.getRect().contains( sf::Mouse::getPosition(win) )
    && sf::Mouse::isButtonPressed( sf::Mouse::Left )
    && btnclock.getElapsedTime().asSeconds() > 2 )
                {
                    srv.Start(btnclock);
                }





                if ( btngrid.getRect().contains( sf::Mouse::getPosition(win) )
    && sf::Mouse::isButtonPressed( sf::Mouse::Left )
    && btnclock.getElapsedTime().asSeconds() > 2 )
                {
                                     sf::Packet packet;
                       sf::Int32  _id = 106;
                        packet << _id;
                                _id = cube.size();
                        packet << _id;
                       for ( int i = 0; i < cube.size(); i++ )
                       {
                        std::string str = cube[ i ];
                        packet << str;
                       }

                         std::uniform_int_distribution< int > idist( 0, srv.amount - 1 );
                         _id = idist( rgen );
                        packet << _id;


                       srv.sendAll( packet );
                }




if ( btnconnect.getRect().contains( sf::Mouse::getPosition(win) )
    && sf::Mouse::isButtonPressed( sf::Mouse::Left )
    //&& btnclock.getElapsedTime().asSeconds() > 2 )
                )
                {
                                              sf::Packet packet;
                       sf::Int32  _id = 107;
                        packet << _id;
                                _id = cube.size();
                        packet << _id;
                       for ( int i = 0; i < cube.size(); i++ )
                       {
                        std::string str = cube[ i ];
                        packet << str;
                       }

                         std::uniform_int_distribution< int > idist( 0, srv.amount - 1 );
                         _id = idist( rgen );
                        packet << _id;


                       srv.sendAll( packet );

                        packet.clear();
                         std::vector< sf::Int32 > vIds;
                         for ( int i = 0; i < srv.clients.size() ; i++ )
                         {
                            vIds.push_back( i );
                         }
                        std::random_shuffle(vIds.begin(), vIds.end());

                        packet << _id;
                        _id = vIds.size();
                        packet << _id;
                        for ( auto x : vIds )
                            packet << x;

                        int z = 0;
                        {
                            for ( auto x : srv.clients )
                            {
                            packet.clear();

                            _id = 109; /// järkkä
                            packet << _id;
                            _id = vIds[ z ];
                            packet << _id;
                            x->send( packet );
                                z++;

                            }
                        }


                }




            }








            win.clear( sf::Color( 100, 100, 100, 255 ) );


            win.draw(text);
            btnhost.draw(win);
            btnconnect.draw(win);
            btngrid.draw(win);
            ppl.draw(win);
            win.draw(btnhost.text);

            win.display();
    }



}
