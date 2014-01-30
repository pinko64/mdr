#ifndef SERVER_H
#define SERVER_H
#include <sfml/network.hpp>
#include <iostream>

#include "deckwriter.h"

#include <map>
#include <list>
#include <thread>


enum class pckType
{
    CHAT
};

/// void (X::* ptfptr) (int) = &X::f;
class Server
{
    public:
        Server(int _portin);

        void Start(sf::Clock &clock);



        sf::Clock           clock;
        bool               ServerActive;
        sf::SocketSelector SockS;
        std::list<sf::TcpSocket*> clients;
        std::thread              threadServer;

        ///people connected
        std::vector<std::string>  ppl;
        std::map< int, std::string > map;
        int                       count;

        int                    amount;

        void                     sendAll(sf::Packet& _packet);

        //std::vector<Card>        &cards;
        bool          HandlePacket(sf::Packet&, sf::TcpSocket &_client);
        void          hostLoop();
        bool          isHost;
        sf::TcpSocket outsocket;
        sf::TcpSocket socket;
        sf::TcpSocket client;
        sf::TcpListener listener;
        std::string    ipOut;
        int            portOut;
        int            portIn;

        std::map<std::string,std::string> vMessages;
//        Player      &plr;
        bool Loop();
        bool sendChat(std::string&);

        virtual ~Server();
    protected:
    private:
};

#endif // SERVER_H
