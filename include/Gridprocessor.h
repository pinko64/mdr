#ifndef GRIDPROCESSOR_H
#define GRIDPROCESSOR_H
#include <sfml/system.hpp>
#include <sfml/graphics.hpp>
#include "../fetcher.h"


class Gridprocessor
{
    public:
        Gridprocessor(  );
        virtual ~Gridprocessor();
        sf::Texture  back;

        void                     setCube( std::vector<std::string> );
        std::vector<std::string> cube;
        std::vector< sf::Text >  vTexts;
        sf::Font                  font;
        std::vector<sf::IntRect> vRects;
        std::vector<sf::RectangleShape> vShapes;
        void getimgs(  );
        int      current;

        void arrange(  );

    protected:
    private:
};

#endif // GRIDPROCESSOR_H
