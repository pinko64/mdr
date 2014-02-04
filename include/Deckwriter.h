#ifndef DECKWRITER_H
#define DECKWRITER_H

#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <time.h>



class Deckwriter
{
    public:
        Deckwriter();
        virtual ~Deckwriter();
        void     write(std::vector<std::string>&, std::string);

    protected:
    private:
};

#endif // DECKWRITER_H
