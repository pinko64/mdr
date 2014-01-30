#ifndef DRAFTPROCESSOR_H
#define DRAFTPROCESSOR_H
#include <sfml/graphics.hpp>
#include "../fetcher.h"


class DraftProcessor
{
    public:
        DraftProcessor();



        sf::Texture  back;

        void                     setBoosters( std::vector<std::string> );
        std::vector<std::string> cube;
        std::vector< sf::Text >  vTexts;
        sf::Font                  font;
        std::vector<sf::IntRect> vRects;
        std::vector<sf::RectangleShape> vShapes;
        void getimgs(  );
        int      current;

        void arrange(  );


        virtual ~DraftProcessor();
    protected:
    private:
};

#endif // DRAFTPROCESSOR_H
