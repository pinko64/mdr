#include "Fetcher.h"


std::map<std::string, sf::Texture*>  Fetcher::mTextures;

Fetcher::Fetcher( std::vector<std::string> _v ) :
    http("http://mtgimage.com")
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

long Fetcher::GetSize(std::string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
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


            mkdir("\img");




            for (int i = 0; i < v.size(); i++)
            {
                std::string _name = v[i];

                /// i o
                std::ifstream exists( "img/" + _name + ".jpg" );
                if  ( !exists.good() || GetSize( "img/" + _name + ".jpg") == 0  )
                {

                request.setUri( "/card/"+_name+".jpg" );


                sf::Http::Response response = http.sendRequest(request);
                ///request.setUri( par.parse( response.getBody() ) );
                response = http.sendRequest( request ); ///Fetch the image from url;

                std::string img = response.getBody();
                sf::Texture *txr = new sf::Texture;
                //sf::Image   simg;
                std::ofstream file( "img/" + _name + ".jpg", std::ios::binary );
                file.write( response.getBody().c_str(), response.getBody().size() );
                file.close();


                txr->loadFromMemory( img.data(), img.size() );// = *response;
                //vtxtr.push_back( txr ); // returns a copy
                txr->setSmooth( 1 );
                mTextures[_name] =  txr;
                //vTextures.push_back( txr );

                }
                else
                {
                    sf::Texture *txr = new sf::Texture;
                    txr->setSmooth( 1 );
                    //txr->setRepeated( 1 );
                    txr->loadFromFile( "img/" + _name + ".jpg" );
                    mTextures[_name] = txr;
                }


}}

