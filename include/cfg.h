#ifndef CFG_H
#define CFG_H
#include <iostream>
#include <string>
#include <fstream>

class cfg
{
    public:
        cfg();
        int            getIncomingPort();
        std::string    getName();
        std::string    getIpToConnect();
        int            getPortToConnect();
        bool           getIsHost();
        virtual ~cfg();
    protected:
    private:
};

#endif // CFG_H
