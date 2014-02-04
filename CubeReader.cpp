#include "CubeReader.h"


CubeReader::CubeReader()
{
    //ctor
}

CubeReader::~CubeReader()
{
    //dtor
}

std::vector<std::string> CubeReader::operator()( std::vector< std::string > &vr )
{

    std::size_t swp = 0;
    std::vector< std::string > cube;

    std::string str;
    std::string temp;
    int number;

    for ( int i = 0; i < vr.size(); i++ )
    {
        str = vr[ i ];
        swp = str.find( "\"" );
        //std::cout << str << std::endl;
        if ( swp != std::string::npos )
        {
            str.erase( swp, 1 );
            swp = str.find( "\"" );
            temp.assign( str, 0, swp );

            str.erase( 0, swp+1 );
            for ( int i = 0; i < 4; i++ )
            {
                swp = str.find( "," );
                str.erase( 0, swp + 1 );
            }
            swp = str.find( "," );
            str.erase( swp, std::string::npos );
            temp += ";" + str;

            cube.push_back( temp );


        }
    }






    return cube;


}


std::vector<std::string> CubeReader::read(std::string filename)
{
///std::vector<Card> vCards;



    std::vector< std::string > cube;


    std::size_t swp = 0;

    std::string str;
    std::string temp;
    int number;

    std::ifstream infile;
    infile.open(filename);


    while(getline(infile,str))
    {
        if ( *str.begin() == '"' )
        cube.push_back( str ); ///Write to cube1. unedited.
    }
    infile.close();
    ///Shuffle deck:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937_64 gt ( seed );
    srand ( gt() );
    std::random_shuffle( cube.begin(), cube.end() );



    return cube;




}
