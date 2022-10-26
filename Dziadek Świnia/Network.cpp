#include <fstream>
#include <string>

#include "Network.hpp"

Network::Network()
{
    std::fstream file;
    file.open("netConfig.txt",std::ios::in);
    if(file.good())
    {
        std::string content;
        getline(file,content);
        if(content=="serwer"){
            Type=serwer;
        }else if(content=="klient"){
            Type=klient;
        }else if(content=="" || file.eof())
        {

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

Network::~Network()
{
    //socket.close();
}
void Network::Odbierz(AI &przeciwnik,unsigned int HP1)
{
    sf::Vector2f bulletPos[10];
    bool leci[10];

    //unsigned int received;
    sf::Packet pack;
    socket.receive(pack);
    pack>>HP1;
}
void Network::Wyslij(Postac &postac,float x,unsigned int HP2,bron *Bron)
{
    sf::Packet pack;
    socket.send(pack);
    pack>>HP2>>Bron->Bullet>>x;
}
void Network::Update(Postac &postac,AI &przeciwnik,float x,unsigned int HP1,unsigned int HP2,bron *Bron)
{

    if(Type==serwer)
    {
        listener.accept(socket);
    }
    Wyslij(postac);
    Odbierz(przeciwnik);
}
/*
Zawartosc paczki:
-HP
-Vectory Pociskow
-Czy pocisk leci

*/
