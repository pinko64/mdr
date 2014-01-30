#include "Fetcher.h"


std::map<std::string, sf::Texture*>  Fetcher::mTextures;

Fetcher::Fetcher( std::vector<std::string> _v ) :
    http("http://magiccards.info/")
{
    request.setHttpVersion(1,1);
    request.setMethod(sf::Http::Request::Get);

    std::string c;
    tr1 = std::thread(&Fetcher::Fetch, this, _v );

}

Fetcher::~Fetcher()
{
    //dtor
}


/*
sf::Texture Fetcher::Fetch(std::string _name)
{
///                    query?q=goblins
                //    _name = "balance";
                request.setUri( "/query?q=" + _name );


                sf::Http::Response response = http.sendRequest(request);

                request.setUri( par.parse( response.getBody() ) );
                response = http.sendRequest( request ); ///Fetch the image from url;

                std::string img = response.getBody();
                sf::Texture txr;
                sf::Image   simg;

                for (int i = 0; i < 30; i++)
                {
                    std::cout << img[i];
                }
                txr.loadFromMemory( img.data(), img.size() );// = *response;
                return txr; // returns a copy

}
*/
void Fetcher::Fetch(std::vector<std::string> v)
{
        std::cout << "vector size on : " << v.size() << std::endl;


            std::vector< std::shared_ptr< sf::Texture > > vtxtr;
            if ( v.size() > 0 )
                {

            for (int i = 0; i < v.size(); i++)
            {
                std::string _name = v[i];
                std::cout << _name << std::endl;

                request.setUri( "/query?q=" + _name );


                sf::Http::Response response = http.sendRequest(request);
                request.setUri( par.parse( response.getBody() ) );
                response = http.sendRequest( request ); ///Fetch the image from url;

                std::string img = response.getBody();
                sf::Texture *txr = new sf::Texture;
                //sf::Image   simg;
/*
                for (int i = 0; i < 30; i++)
                {
                    std::cout << img[i];
                }
                */
                txr->loadFromMemory( img.data(), img.size() );// = *response;
                //vtxtr.push_back( txr ); // returns a copy
                mTextures[_name] =  txr;
                //vTextures.push_back( txr );

            }
            }


}

