#include "cfg.h"

cfg::cfg()
{
    //ctor
}

cfg::~cfg()
{
    //dtor
}


int            cfg::getIncomingPort()
{
std::ifstream infile;
std::string tmp;
int ret;
infile.open("cfg/in.cfg");
    getline(infile,tmp);
    ret = std::stoi(tmp);
    return ret;
}



std::string    cfg::getName()
{
std::ifstream infile;
std::string tmp;
infile.open("cfg/name.cfg");
    getline(infile,tmp);
    return tmp;
}



bool    cfg::getIsHost()
{
std::ifstream infile;
std::string tmp;
int ret;
infile.open("cfg/ishost.cfg");
    getline(infile,tmp);
    ret = std::stoi(tmp);
    return ret;


}



std::string    cfg::getIpToConnect(){
std::ifstream infile;
std::string tmp;
infile.open("cfg/out.cfg");
    getline(infile,tmp);
    return tmp;
}



int            cfg::getPortToConnect()
{
std::ifstream infile;
std::string tmp;
int ret;
infile.open("cfg/outport.cfg");
    getline(infile,tmp);
    ret = std::stoi(tmp);
    return ret;


}
