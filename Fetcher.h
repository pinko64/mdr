#ifndef FETCHER_H
#define FETCHER_H
#include <sfml/network.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <dir.h>
#include "htmlparser.h"
#include <sys/stat.h>
#include <memory>
#include <thread>
#include <map>
#include <sfml/graphics.hpp>

class Fetcher
{
    public:

        Fetcher( std::vector<std::string> _v );
        //sf::Texture Fetch(std::string);

        long    GetSize(std::string filename);

        void Fetch(std::vector<std::string>);
        htmlparser par;

        static std::map<std::string, sf::Texture*>  mTextures;
        std::map<std::string, sf::Texture*>::iterator it;

        std::vector<std::shared_ptr< sf::Texture > > vTextures;
        std::thread tr1;
        sf::Http  http;
        sf::Http::Request request;
        virtual ~Fetcher();
    protected:
    private:
};

#endif // FETCHER_H
