#include "Fetcher.h"


std::map<std::string, std::unique_ptr<sf::Texture> >  Fetcher::mTextures;

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

void Fetcher::Fetch( std::vector<std::string> v)
{

    std::string set;
    std::string setdir;
    size_t swp = 0;
    mkdir("\img");

    getTrim();
    size_t pos;

    for (int i = 0; i < v.size(); i++)
    {

        /// Get setname...
        std::string set;
        pos = v[i].find( ";" );
set.assign( v[i], pos + 1, std::string::npos );
        v[i].erase( pos, std::string::npos );

        for ( auto &x : set )
            x = tolower( x );

        std::map< std::string, std::string >::iterator it;
        it = mTrim.find( set );
        if ( it != mTrim.end() )                    ///Trimming operation
        {
            set = it->second;//mTrim.find( set )->second << std::endl;
        }

        swp = v[i].find( "Æ" );
        if ( swp!=std::string::npos )
        {
     //       v[i].replace( swp-1, 3, 1, ' ' );
            v[i][swp] = 'a';
            v[i].insert( swp+1, "e" );
        }
        std::replace( v[i].begin(), v[i].end(), '/', '_');
        std::replace( v[i].begin(), v[i].end(), ' ', '_');
        ///std::cout << "sisainen: " << v[i] << std::endl;
        ///

            std::string _name = v[i];
            request.setUri( "/set/" + set + "/" + _name + ".jpg" );

            if ( set == "CON" || set == "con" ) /// CON is reserved in dos....
            {
                set += 'f';
            }
            if ( set== "BLANK" || set == "blank" )
                request.setUri( "/card/" + _name + ".jpg" );


        std::ifstream exists( "img/" + set + "/" + _name + ".jpg" );
        if  ( !exists.good() || GetSize( "img/" + set + "/" + _name + ".jpg") == 0  )
        {






            sf::Http::Response response = http.sendRequest(request);
            ///request.setUri( par.parse( response.getBody() ) );
            response = http.sendRequest( request ); ///Fetch the image from url;

            std::string img = response.getBody();

            //sf::Image   simg;
            std::ofstream file( "img/" + set + "/" + _name + ".jpg", std::ios::binary );
            file.write( response.getBody().c_str(), response.getBody().size() );
            file.close();

            std::unique_ptr< sf::Texture > txr( new sf::Texture );
            txr->loadFromMemory( img.data(), img.size() );// = *response;
            //vtxtr.push_back( txr ); // returns a copy
            txr->setSmooth( 1 );
            //std::cout << "Loading from memory to " << _name << std::endl;


            std::replace( _name.begin(), _name.end(), '_', ' ');
            mTextures[_name] =  std::move( txr );


            //vTextures.push_back( txr );

        }
        else
        {

            std::unique_ptr< sf::Texture > txr( new sf::Texture );
            txr->setSmooth( 1 );
            //txr->setRepeated( 1 );
            txr->loadFromFile( "img/" + set + "/" + _name + ".jpg" );

            std::replace( _name.begin(), _name.end(), '_', ' ');
            mTextures[_name] =  std::move( txr );
            //  std::cout << "ELSE " << _name << std::endl;
        }


    }
}


void Fetcher::getTrim(  )
{
std::string s1,s2,str;
std::ifstream infile;

std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
str.erase(end_pos, str.end());
        size_t temp;
    infile.open( "trim.txt" );

    while( getline(infile,str) )
    {
        temp = str.find( ',' );
        s1 = str.substr( 0, temp );
        std::string::iterator end_pos = std::remove(s1.begin(), s1.end(), ' ');
        s1.erase(end_pos, s1.end());

        s2 = str.substr( temp + 1, str.size() - (temp + 1) );
        end_pos = std::remove(s2.begin(), s2.end(), ' ');
        s2.erase(end_pos, s2.end());

        for ( auto &x : s1 )
            x = tolower( x );
        for ( auto &x : s2 )
            x = tolower( x );
        ///std::cout << "1 : " << s1 << "    2: " << s2 << std::endl;

        mTrim[ s1 ] = s2;

    }
    infile.close();


}

