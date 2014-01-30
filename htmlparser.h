#ifndef HTMLPARSER_H
#define HTMLPARSER_H
#include <sfml/network.hpp>
#include <iostream>
#include <string>

class htmlparser
{
    public:
        htmlparser();
        std::string parse(std::string _html);
        virtual ~htmlparser();
    protected:
    private:
};

#endif // HTMLPARSER_H
