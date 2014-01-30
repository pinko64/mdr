#include "Server.h"

Server::Server(int _portin) :
portIn(_portin),
ServerActive(0),
amount(0)
{


        //threadServer =  std::thread(&Server::hostLoop,this);
}


void Server::Start(sf::Clock &clock){

if (!ServerActive)
{

threadServer =  std::thread(&Server::hostLoop,this);
clock.restart();

}
}



Server::~Server()
{
    //dtor
}


void Server::hostLoop()
{
ServerActive = 1;

std::cout << "Server loop starting" << std::endl;
std::cout << "clientsize= " << clients.size() << std::endl;
sf::Clock clock;

listener.listen(portIn);
///listener.accept(sock);
SockS.add(listener);
int clientsn;
while (ServerActive)
{
sf::Time t1 = sf::seconds(0.3f);

    if (SockS.wait(t1))
    {
        if (SockS.isReady(listener))
        {

            sf::TcpSocket* client = new sf::TcpSocket;
            if (listener.accept(*client) == sf::Socket::Done)
            {

                clients.push_back(client);
                SockS.add(*client);
                ///std::cout << client->getRemoteAddress();
                sf::Packet pkt;
                sf::Int32  _id = 125;
                sf::Int32  id = amount;

                pkt << _id << id;
                amount++;
                client->send( pkt );

                clientsn++;

            }
            else
            {
             delete client;
            }
        }
          else
        {
         for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
         {
            sf::TcpSocket& client = **it;
                if (SockS.isReady(client))
                {

                    sf::Packet packet;
                    if (client.receive(packet) == sf::Socket::Done)
                    {


                        {



                        HandlePacket(packet, client);


                        }

                    }
                }
                //if (!clients.size() == clientsn)


         }

        }



        }
    }


std::cout << "end of thread" << std::endl;




}





bool Server::sendChat(std::string &_packet)
{
        sf::Packet p1;
}




void Server::sendAll(sf::Packet& _packet)
{
    for (std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
    {
             sf::TcpSocket& client = **it;
             client.send(_packet);
    }
}



bool Server::HandlePacket(sf::Packet& packet, sf::TcpSocket &_client)
{
std::cout << "handling packet ..." << std::endl;

  //  for (int i = 0; i < cards.size(); i++)
//    std::cout << cards[i].Name << " ---";


sf::Int32 a;
packet >> a;

if ( a == 10 )
{
    std::cout << "Going great";
    std::string name;
    packet >> name;
    ppl.push_back( name );
   std::cout << "received: " << name << std::endl;
    sf::Packet pplpkt;
    sf::Int32 I = 105;
    pplpkt << I;
    I = ppl.size();
    pplpkt << I;
    for ( int i = 0; i < ppl.size(); i++ )
    {
        pplpkt << ppl[i];
        std::cout << std::endl << std::endl;
        std::cout << ppl[ i ] << std::endl << std::endl;
    }
    sendAll(pplpkt);

}


if ( a == 110 )
{
    sf::Packet pkt;
    sf::Int32 id = 110;
    pkt << id;


    for (int i = 0; i < 3; i++)
    {
        sf::Int32 iz;
        packet >> iz;
        pkt << iz;
    }




    sendAll(pkt);

}

if ( a == 113 )
{
    sf::Int32 _id = 114;
    sf::Int32 id;
    packet >> id;
    sf::Int32 destroyed;
    packet >> destroyed;

    packet.clear();
    packet << _id << id << destroyed;
    sendAll( packet );


}

if ( a == 145 )
{
    std::string name;
    sf::Int32 amount;
    std::vector< std::string > vDeck;
    packet >> name >> amount;
    for ( int i = 0; i < amount; i++ )
    {
        std::string cardname;
        packet >> cardname;
        vDeck.push_back( cardname );
    }
    Deckwriter dwriter;
    dwriter.write( vDeck, name );
}




return 1;

}


