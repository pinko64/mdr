#include "htmlparser.h"

htmlparser::htmlparser()
{
    //ctor
}

/// <img src="http://magiccards.info/scans/en/fve/1.jpg"
htmlparser::~htmlparser()
{
    //dtor
}


std::string htmlparser::parse(std::string _html)
{

    //sf::Http::Response::getBody()
    std::string url = "";

    std::size_t first = _html.find( "/scans/" ); ///22 ois http alku
    std::size_t second = _html.find( ".jpg\"" );
    if ( first!=std::string::npos )
    {
        std::cout << "FOUND IT" << std::endl;

        for ( int i = first; i < second + 4; i++ )
        {
            url.push_back( _html[i] );
        }

    }
    std::cout << url;

return url;
}

