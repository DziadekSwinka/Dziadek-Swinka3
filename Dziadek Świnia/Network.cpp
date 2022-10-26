#include <fstream>
#include <string>

#include "Network.hpp"

Network::Network()
{
    std::fstream file;
    file.open("netConfig.txt",std::ios::in);
    if(file.good() && !file.eof())
    {
        std::string content;
        getline(file,content);
        if(content=="serwer"){
            Type=serwer;
        }else if(content=="klient"){
            Type=klient;
        }else
        {
            std::string e="Zly tekst pliku";
            throw (e);
        }

        if(Type==klient)
        {
            std::string ip;
            getline(file,ip);
            IP=static_cast<sf::IpAddress>(ip);
            if(socket.connect(IP,port)!=sf::Socket::Done){
                std::string e="Nie udalo sie polaczyc z "+IP.toString();
                throw (e);
            }
        }
        if(Type==serwer)
        {
            if(listener.listen(port)!=sf::Socket::Done){
                std::string e="Nie moge rozpoczac nasluchiwania na porcie "+std::to_string(port);
                throw (e);
            }
        }
    }else
    {
        std::string e="Nie mozna otworzyc pliku";
        throw (e);
    }
}

void Network::Update()
{

}
