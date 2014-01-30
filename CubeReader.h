#ifndef CUBEREADER_H
#define CUBEREADER_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


class CubeReader
{
    public:
        CubeReader();
        //Fetcher           fetcher;
        std::vector<std::string> read(std::string filename);
        std::string       cubename;
        std::vector<std::string> vCard;



        virtual ~CubeReader();
    protected:
    private:
};

#endif // CUBEREADER_H
