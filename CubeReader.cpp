#include "CubeReader.h"


CubeReader::CubeReader()
{
    //ctor
}

CubeReader::~CubeReader()
{
    //dtor
}


std::vector<std::string> CubeReader::read(std::string filename)
{
///std::vector<Card> vCards;



std::size_t swp = 0;

std::string str;
int number;

std::ifstream infile;
infile.open(filename);
    while(getline(infile,str))
    {


        number = std::stoi(str);

        str.erase(str.begin(),str.begin()+2);
        swp = str.find("/");
        if (swp!=std::string::npos){
            str.replace(swp-1,3,1,' ');
            //std::replace(str.begin(),str.end(), ' ', '_');
        }
         std::replace(str.begin(),str.end(), ' ', '_');
        //if (str.find()) std::cout << "found" << std::endl;
        ///fetcher.Fetch(str);
//            std::cout << str << std::endl;

        //std::cout << number << std::endl;
        //std::cout << str << std::endl;
        swp = 0;
        ///std::cout << str << "    -    ";
        //Card c1(str);
        //c1.CardTexture.loadFromFile("img/" + str + ".jpg");
        //c1.CardSprite.setTexture()
        vCard.push_back(str);


    }
//fetcher.Fetch("call of the herd");
//fetcher.Fetch("call_of_the_herd");
return vCard;
}
