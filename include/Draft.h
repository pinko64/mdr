#ifndef DRAFT_H
#define DRAFT_H
#include <sfml/audio.hpp>

#include "server.h"
#include "../client.h"
#include "people.h"
#include "window.h"
#include "stack.h"
#include "draftprocessor.h"
#include "../fetcher.h"
#include "deckwriter.h"

#include <sstream>



class Draft
{
    public:
        Draft( sf::RenderWindow& _win, Server &_srv, Client &_clt, People &_ppl, std::vector<std::string>  &_cube, Stack &_stack );

        void Loop();
        Stack           &stack;
        DraftProcessor  dproc;
        Deckwriter        dwriter;

        sf::Font           font;
        sf::RectangleShape zoom;
        sf::Clock          zoomclock;

        int                timeLimit = 15 * 2;
        sf::Clock          timer;
        sf::Text           txtTimer;

        sf::SoundBuffer    sndbufferNewSet;
        sf::SoundBuffer    sndbufferTick;
        sf::Sound   sndNewSet;
        sf::Sound    sndTick;

        std::vector<std::string> vDeck;
        int                num;
        int                round;
        int                getNum();
        void               Next();
        void               Shoot();

        void               preShoot( int );

        bool               Wait( bool );
        bool               wait;

        sf::Clock          shootclock;


        int                                      isOn();

        std::vector< std::string >                &cube;
        std::vector< std::vector< std::string > > vBoosters;

        People           &ppl;
        Client           &clt;
        Server           &srv;
        sf::RenderWindow &win;

        virtual ~Draft();
    protected:
    private:
};

#endif // DRAFT_H
