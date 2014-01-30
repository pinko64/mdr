#include "Deckwriter.h"

Deckwriter::Deckwriter()
{



    //ctor
}

Deckwriter::~Deckwriter()
{
    //dtor
}


void Deckwriter::write(std::vector<std::string>& _cards, std::string _name)
{


    std::ofstream file(_name + ".dec",  std::ios_base::trunc);
    if (file.is_open())
    {
    std::cout << "kortteja: " << _cards.size() << std::endl;
        for (int i = 0; i < _cards.size(); i++)
        {
            std::replace(_cards[i].begin(),_cards[i].end(), '_', ' ');
            file << "1 " << _cards[i] << std::endl;
///            std::cout << "card: " << _cards[i] << std::endl;

        }
        file.close();
    }


}
