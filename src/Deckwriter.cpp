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

    time_t rawtime;
    struct tm * ptm;

    time ( &rawtime );
    ptm = gmtime ( &rawtime );

    std::string hour = std::to_string( ptm->tm_hour );
    std::string month = std::to_string( ptm->tm_mon );
    std::string year = std::to_string( ptm->tm_year );
    year.erase( 0, 1 );


///Card Name,Quantity,ID #,Rarity,Set,Collector #,Premium,Sideboarded,
//    std::ofstream file( _name + year + month + hour + ".dec",  std::ios_base::trunc );
        std::ofstream file( _name +  ".dek",  std::ios_base::trunc );
    if (file.is_open())
    {

        file << "Card Name,Quantity,ID #,Rarity,Set,Collector #,Premium,Sideboarded," << std::endl;
        for (int i = 0; i < _cards.size(); i++)
        {
            ///std::replace(_cards[i].begin(),_cards[i].end(), '_', ' ');
            file <<  _cards[i] << std::endl;
///            std::cout << "card: " << _cards[i] << std::endl;

        }
        file.close();
    }


}
