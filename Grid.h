#ifndef GRID_H
#define GRID_H
#include <sfml/graphics.hpp>
#include <iostream>
#include "server.h"
#include  <random>
#include  <iterator>
#include "client.h"
#include "fetcher.h"
#include <stdio.h>
#include <chrono>
#include "gridprocessor.h"
#include "deckwriter.h"
#include "stack.h"

#include "people.h"

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}




class Grid
{
    public:
        Grid( sf::RenderWindow&, Server &_srv, Client &_client, Stack&, People &_ppl );
        virtual ~Grid();
            sf::RenderWindow &rWin;

                        Gridprocessor   gp;




                int             checknumber;
                bool            End;
                sf::Text        txtEnd;

                Stack           &stack;
                void            checkRow();
                std::vector<std::string> deckout;
                Deckwriter        dwriter;
                sf::RectangleShape zoom;
                sf::Clock          zoomclock;
                std::vector<std::string> cube;
                std::vector<std::string> own;

                std::vector<std::vector<std::string>> alldecks;

                People             &ppl;

                 bool isHost;

                int      State;
                bool     newDeck;

                void        nextTurn();
                std::string whosTurn;
                bool myTurn;
                void Start();

                sf::Text sfTxt;
                sf::Font sfFont;
                sf::String sTr;





            sf::Clock   shootClock;
            sf::Clock   shootclock;


            Server       &srv;
            Client  &client;

            std::vector<sf::IntRect> iRect;
            void temp(); ///
            void Shoot(std::vector<int> &_ints);
            void preShoot(std::vector<int> &_ints);

            /// Store blabla
            int Current;
            void Allocator();



            std::vector<int> Friends(int,bool _alt);  ///get friendcards...
            void ResizeSprites(int);
            void Align();


            sf::Texture ArrowTexture;
            std::vector<sf::Sprite> sprArrow;
        bool isRunning;
        void Loop( std::vector<std::string> &_deck );
    protected:
    private:
};

#endif // GRID_H
