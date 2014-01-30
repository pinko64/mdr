#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include <sfml/network.hpp>
#include <thread>
#include <memory>

#include <iostream>
#include "stack.h"
#include "people.h"

class Grid;
class Manager;


/// void (X::* ptfptr) (int) = &X::f;

class Client
{
    public:
        Client(std::string _ipout, int _portout,  Manager* pmgr, Stack &stack, People &_ppl, std::string _name);

//        void                 (Manager::* ptr) () = &Manager::test;
        Stack                 &stack;
        People                &ppl;

        std::string           ipout;
        std::string           name;
        void         setname(std::string str);
        std::string           getname();

        Manager              *pmgr;
//        int                  pmgr;
        void                 setManager(Manager&);


        int                  portout;
        sf::TcpSocket  socket;
        std::thread              threadClient;
        void tryConn();

        std::vector<int>     row;
        //Grid        &grid;
//        Grid        *gay;


        void  Send(sf::Packet&);

//1        Grid &grid_object
        //std::auto_ptr<Grid>    ptr;

        //.ptr = std::auto_ptr<Grid>(this);
        //std::vector<std::string> cards;
        //std::vector<std::string> ppl;

        bool                    ClientActive;
/*
        void                    *newDeck;
        void                    *state;
        void                    *getPpl;
        void                    *whosTurn;
        void                    *hasRow;
        void                    *nexTurn;
        void (Grid::*fptr)(std::vector<int> &);
*/


            std::vector<int>     getRow();
            //connecteds;

//        void (Grid::*ptr)(std::vector<int>&) const;


        void  HandlePacket(sf::Packet&);
        void Loop();
        virtual ~Client();
    protected:
    private:
};

#endif // CLIENT_H
