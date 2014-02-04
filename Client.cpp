#include "Client.h"

Client::Client(std::string _ipout, int _portout, Manager* pmgr, Stack &_stack , People &_ppl, std::string _name ) :
    ClientActive(1),
    ipout(_ipout),
    portout(_portout),
    stack(_stack),
    ppl(_ppl),
    name(_name)
{

 //   pmgr->loop();

threadClient = std::thread(&Client::tryConn,this);

}

void Client::tryConn()
{

bool isCon = 0;
while (!isCon && ClientActive){
sf::Socket::Status status;
    status = socket.connect(ipout,portout);

if (status != sf::Socket::Done)
{
    ///std::cout << "Error while trying to connect client socket. Trying again." << std::endl;
}
else if (status == sf::Socket::Done)
{
     isCon = true;
     sf::Packet packet;
     sf::Int32  id = 10;
      packet << id << name;
     Send(packet);
}
}








Loop();

}

Client::~Client()
{
    //dtor
}

void setManager(Manager& mg)
{
 //Manager *pmgr;
  //  pmgr = &mg;
//    pmgr->loop();
}


void Client::Loop()
{

    sf::Clock clock;
    socket.setBlocking(1);
    while (ClientActive)
    {
        if (clock.getElapsedTime().asSeconds() > 0.4)
        {
                sf::Packet packet;
                packet.clear();
                socket.receive(packet);
                HandlePacket(packet);
                clock.restart();
        }



    }

        std::cout << "client is not active.";

}


void Client::Send(sf::Packet &_packet)
{

 socket.send(_packet);
}


void  Client::HandlePacket(sf::Packet& packet)
{
//std::cout << "client package" << std::endl;
sf::Int32 id;

    packet >> id;

    std::cout << id << std::endl;
    if (id == 105)
    {

    sf::Int32 size;
    packet >> size;
    //stack.addName( vppl );

    std::vector<std::string> vppl;
    for ( int i = 0; i < size; i++ )
    {
        std::string str;
        packet >> str;

       vppl.push_back( str );
        //stack.addName( str );
        ppl.addppl( str );
    }
    ppl.addppl( vppl );


    }


if (id == 106) // start grid;  + give deck;
    {
     sf::Int32 num;
     packet >> num;
     std::vector< std::string > vstr;

     for ( int i = 0; i < num; i++ )
     {
        std::string s;
        packet >> s;
        vstr.push_back( s );
     }

        stack.addCube( vstr );

     packet >> num;
     stack.whosTurn = num;

     stack.gridison = 1;
     stack.hasCube = 1;

    }



if (id == 107) // start draft;  + give deck;
    {
     sf::Int32 num;
     packet >> num;
     std::vector< std::string > vstr;

     for ( int i = 0; i < num; i++ )
     {
        std::string s;
        packet >> s;
        vstr.push_back( s );
     }

        stack.addCube( vstr );
        stack.hasCube = 1;
     //packet >> num;
     //stack.whosTurn = num;

     stack.draftison = 1;

    }


    if (id == 109) // start draft;  + get järkkäid
    {

     int x;
     packet >> x;
     stack.ID = x;



    }

    if ( id == 114 )
    {
        sf::Int32 id, dest;
        packet >> id >> dest;
        destroyed d1( id, dest );
        stack.vDestroyed.push_back( d1 );
        stack.pplREADY++;
    }






if (id == 110) //turn
{
    sf::Int32 a;
    for ( int i = 0; i < 3; i++ )
    {
        packet >> a;
        stack.Row.push_back( a );
}}

if (id == 125) //turn
{
    sf::Int32 ID;
    packet >> ID;
    stack.ID = ID;




}
}









/*
    else if (id == 11)
        {

        row.clear();
        int a, b, c;
        packet >> a >> b >> c;

        row.push_back(a);row.push_back(b);row.push_back(c);
        packet.clear();
        //std::string *pString = static_cast<std::string*>(grid);
//        *pString = name;


         //(ptr(ints);
//        std::cout << "It is " << name << "'s turn." << std::endl;

    }


    else if (id == 100) /// Get Deck
        {

        sf::Int32 sz;
        packet >> sz;
        std::string str;

        for (int i = 0; i < sz; i++)
        {
            packet >> str;

        }

        packet.clear();


        //bool *pString = static_cast<bool*>(hasRow);
  //      *pString = true;

         //(ptr(ints);
//        std::cout << "It is " << name << "'s turn." << std::endl;

    }




    else if (id == 13)
        {



        //(ptr(ints);
//        std::cout << "It is " << name << "'s turn." << std::endl;

    }
*/









std::vector<int>     Client::getRow()
{
return row;


}

void Client::setname(std::string str){

name = str;



}

std::string Client::getname(){

return name;



}



