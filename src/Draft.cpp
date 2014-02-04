#include "Draft.h"
std::string float2Str (float number)
{
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}

static inline std::string int2Str(int x)
{
    std::stringstream type;
    type << x;
    return type.str();
}


Draft::Draft( sf::RenderWindow &_win, Server &_srv, Client &_clt, People &_ppl, std::vector<std::string>  &_cube, Stack &_stack  ) :
    win( _win ),
    srv( _srv ),
    clt( _clt ),
    ppl( _ppl ),
    cube( _cube ),
    stack( _stack )
{
    font.loadFromFile( "font.ttf" );
    num = -1;
    wait = false;
    round = 0;


    txtTimer.setFont( font );
    txtTimer.setString( "00" );
    txtTimer.setCharacterSize( 45 );
    txtTimer.setColor( sf::Color::Black );
    txtTimer.setPosition( win.getSize().x - txtTimer.getGlobalBounds().width - 15, win.getSize().y - txtTimer.getGlobalBounds().height - 15 );

    ///load audio
    sndbufferTick.loadFromFile( "sound/clockbeat.wav" );
    sndbufferNewSet.loadFromFile( "sound/newset.wav" );
    sndNewSet.setBuffer( sndbufferNewSet );
    sndTick.setBuffer( sndbufferTick );



    Loop();
    //ctor
}


int Draft::getNum()
{

    if ( stack.ID == 0 )
        ;

}

void Draft::Next()
{




    if ( round == 0 || round == 2 )
        num++;
    else if ( round == 1)
    {
        num--;
        std::cout << num << std::endl;
    }

    if ( round == 0 )
    {
        if ( num > ppl.getppl().size() - 1 )
        {
            num = 0;
        }
    }

    if ( round == 1 )
    {
        if ( num < ppl.getppl().size()  )
        {

            num = ppl.getppl().size() * 2 - 1;

        }
    }


    if ( round == 2 )
    {
        if ( num > ppl.getppl().size() * 3  - 1 )
        {
            num = ppl.getppl().size() * 3 - ppl.getppl().size();
        }
    }


    if ( vDeck.size() == 15 )
    {
        round++;
        dproc.setBoosters( vBoosters[ stack.ID + ppl.getppl().size() ] );
        num = stack.ID + ppl.getppl().size();
        dproc.getimgs();
        dproc.arrange();

    }
    if ( vDeck.size() == 30 )
    {
        round++;
        dproc.setBoosters( vBoosters[ stack.ID + ppl.getppl().size() * 2 ] );
        num = stack.ID + ppl.getppl().size() * 2;
        dproc.getimgs();
        dproc.arrange();

    }
    if ( vDeck.size() == 45 )
    {
        sf::Packet packet;
        ///std::string Name = ppl.getppl()[ stack.ID ].getString();
        std::string Name = stack.myName;
        sf::Int32   _id = 145;
        sf::Int32   amount = vDeck.size();
        packet << _id << Name << amount;
        for ( auto x : vDeck )
            packet << x;

        clt.Send( packet );
        Wait( 1 );
    }

    /*
    dproc.setBoosters( vBoosters[ num ] );
         dproc.getimgs();
         dproc.arrange();
    */

}



void Draft::Shoot()
{

    for ( auto X : stack.vDestroyed )
    {
        vBoosters[ X.x ].erase( vBoosters[ X.x ].begin() + X.y );
        vBoosters2[ X.x ].erase( vBoosters2[ X.x ].begin() + X.y );
    }

    stack.vDestroyed.clear();




//vBoosters[ num ].erase( vBoosters[ num ].begin() + x );
}


bool Draft::Wait( bool x )
{
    sf::Event event;
    while ( win.pollEvent( event ) )
        if ( event.type == sf::Event::Closed )
        {
            close(0);
        }
    win.clear( sf::Color::Black );
    sf::Text t1;
    t1.setFont( font );
    t1.setColor( sf::Color::Red );

    if ( x == 0 )
    {
        t1.setString( " Waiting for other players..." );
    }
    else
        t1.setString( " The draft has ended. Check your name.dek file." );

    win.draw( t1 );
    win.display();

    if ( x == 1 )
        Wait( 1 );


    if ( stack.pplREADY == ppl.getppl().size() )
    {
        stack.pplREADY = 0;

        Shoot();
        Next();
        if ( vDeck.size() != 15 )
        {
            dproc.setBoosters( vBoosters[ num ] );
        }

        dproc.getimgs();
        sndNewSet.play();
        timeLimit = vBoosters[ num ].size() * 2;
        timer.restart();


        return 0;
    }

    return 1;
}

Draft::~Draft()
{
    //dtor
}





void Draft::preShoot( int X )
{
    if ( shootclock.getElapsedTime().asSeconds() > 1 )
    {

        sf::Packet packet;
        sf::Int32  x = 113;
        packet << x;
        x = num;
        packet << x;
        x = X;
        packet << x;
        clt.Send( packet );


///vBoosters[ num ].erase( vBoosters[ num ].begin() + x );
//dproc.setBoosters( vBoosters[ num ] );

        vDeck.push_back( vBoosters2[ num ][ X ] );  /// PROBLEM
//vDeck.push_back( vBoosters[ num ][ X ] );
        for ( auto x : vDeck )
            std::cout << x << std::endl;

        dwriter.write( vDeck, stack.myName );
                      //ppl.getppl()[ stack.ID ].getString() );



//dwriter.write( vDeck, "" );
        wait = true;
        shootclock.restart();
    }

}




int Draft::isOn()
{
    int r = 100;
    for ( int i = 0; i < dproc.vRects.size(); i++ )
    {
        if ( dproc.vRects[i].contains( sf::Mouse::getPosition( win ) ) )
        {
            dproc.vShapes[i].setFillColor( sf::Color::Red );
            r = i;
        }
        else dproc.vShapes[i].setFillColor( sf::Color( 255, 255, 255, 255 ) );
    }
    return r;
}

void Draft::Loop()
{
    win.setTitle( ppl.getppl()[stack.ID].getString() );
    stack.myName = ppl.getppl()[stack.ID].getString();
    focus = 1;
    stack.pplREADY = 0;
    cube = stack.getCube();

    stack.cubeUnedited = cube;

    CubeReader cr;
    cube = cr( cube );

    std::vector< std::string > cube_no_set = cube;
    /// Get setname...
    for ( auto &x : cube_no_set )
    {
        size_t pos;
        pos = x.find ( ";" );
        x.erase( pos, std::string::npos );
        ///std::cout << x << "!!!" << std::endl;
    }



    Fetcher F( cube );


    ///Make boosters...
    vBoosters.resize( ppl.getppl().size() * 3 );
    vBoosters2.resize( ppl.getppl().size() * 3 );

    {
        int a = 0;
        for (int i = 0; i < vBoosters.size() ; i++ )
        {
            for ( int z = 0; z < 15; z++ )
            {
                vBoosters[ i ].push_back( cube_no_set[ a ] );
                vBoosters2[ i ].push_back( stack.cubeUnedited[ a ] );
                a++;
            }
        }
    }

    /*          ///Clone boosters for write output tsädäm...
      vBoosters2.resize( ppl.getppl().size() * 3 );
    { int a = 0;
    for (int i = 0; i < vBoosters2.size() ; i++ )
    {
      for ( int z = 0; z < 15; z++ )
      {
      vBoosters2[ i ].push_back( stack.cubeUnedited[ a ] );
      a++;
      }
    }}
    */

    for ( int i  = 0; i < vBoosters.size(); i++ )
    {
        for ( int e = 0; e < vBoosters[i].size(); e++ )
        {
            size_t test = vBoosters2[i][e].find( vBoosters[i][e] );
            if ( test == std::string::npos )
            {
                std::cout << "ERROR ERROR ERROR ERROR" << std::endl;
            }
            std::cout << vBoosters[i][e] << std::endl;
            std::cout << vBoosters2[i][e] << std::endl << std::endl;
        }
    }
    /*
        str = cube1[ i ];
        swp = str.find( "\"" );
            //std::cout << str << std::endl;
            if ( swp != std::string::npos )
                {
    */
    num = stack.ID;
    std::cout << "SACKID: " << num << std::endl;
    std::cout << "SACKID: " << num << std::endl;
    std::cout << "SACKID: " << num << std::endl;


    dproc.setBoosters( vBoosters[ num ] );
    dproc.getimgs();
    dproc.arrange();



    while ( win.isOpen() )
    {

        sf::Event event;
        while ( win.pollEvent( event ) )
        {
            dproc.getimgs();
            if ( event.type == sf::Event::Closed )
            {
                win.close();
                exit( 0 );
            }
            if ( event.type == sf::Event::LostFocus )
            {
                focus = 0;
            }
            if ( event.type == sf::Event::GainedFocus )
            {
                focus = 1;
            }
        }


        while ( wait )
        {
            wait = Wait( 0 );
        }

        //dproc.getimgs();
        isOn();


        ///
        ///
        ///Timer stuff
        txtTimer.setString( int2Str( timeLimit - (int)timer.getElapsedTime().asSeconds() ) );
        if ( timeLimit - (int)timer.getElapsedTime().asSeconds() == 5 ||
                timeLimit - (int)timer.getElapsedTime().asSeconds() == 4 ||
                timeLimit - (int)timer.getElapsedTime().asSeconds() == 3 ||
                timeLimit - (int)timer.getElapsedTime().asSeconds() == 2 ||
                timeLimit - (int)timer.getElapsedTime().asSeconds() == 1
           )
        {
            sndTick.play();
            txtTimer.setCharacterSize( 60 );
            txtTimer.setColor( sf::Color::Red );
        }
        if ( timeLimit - (int)timer.getElapsedTime().asSeconds() < 0 )
        {
            preShoot( 0 );
            txtTimer.setCharacterSize( 45 );
            txtTimer.setColor( sf::Color::Black );
            timer.restart();
        }




        if ( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && !wait || sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && !wait
                && focus )
        {
            int x = isOn();
            if ( x != 100 )
                preShoot( x );
        }






        if ( sf::Mouse::isButtonPressed(sf::Mouse::Middle)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) )
        {
            int x = isOn();
            if ( x != 100 )
            {
                zoom.setTexture( dproc.vShapes[ x ].getTexture(), true );
                zoom.setSize( sf::Vector2f( 500, 700 ) );
                zoomclock.restart();
            }


        }





        win.clear( sf::Color( 100, 100, 100, 255 ) );

        for ( auto x : dproc.vShapes )
            win.draw( x );

        for ( auto x : dproc.vTexts )
            win.draw( x );

        if (zoomclock.getElapsedTime().asSeconds() < 0.02) win.draw(zoom);

        txtTimer.setPosition( win.getSize().x - txtTimer.getGlobalBounds().width - 15, win.getSize().y - txtTimer.getGlobalBounds().height - 15 );
        win.draw( txtTimer );
        win.display();



    }
}
