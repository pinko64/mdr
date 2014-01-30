#ifndef MANAGER_H
#define MANAGER_H
#include <sstream>
#include <string>
#include "window.h"
#include "button.h"
#include "people.h"

#include <random>
#include "cfg.h"

#include "stack.h"
#include "../client.h"
#include "server.h"
#include "../grid.h"

#include "draft.h"

#include "../Cubereader.h"
//#include "fetcher.h"

class Manager
{
    public:
        Manager( sf::VideoMode _vm, std::string _title, int _refresh );

        cfg                      conf;

        Stack                    stack;

        void                     test();


        People                    ppl;

        Grid                      grid;

        Client                    clt;
        Server                    srv;

        sf::Clock                 btnclock;
        Button                    btnhost;
        Button                    btnconnect;
        Button                    btngrid;
        //load cube
        CubeReader                cubereader;
        std::vector< std::string > cube;

        sf::Font font;
        sf::Text text;



        int   state;  // gamestate     10 = quit
        void  loop();

        Window  Win;
        sf::RenderWindow &win;
        virtual ~Manager();
    protected:
    private:
};

#endif // MANAGER_H
