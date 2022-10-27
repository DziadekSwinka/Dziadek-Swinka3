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
void Network::Odbierz(unsigned int HP2)
{
    sf::Vector2f bulletPos[10];
    bool leci[10];

    //unsigned int received;
    sf::Packet pack;
    socket.receive(pack);
    pack>>HP2;
}
void Network::Wyslij(float x,float y,float angle,unsigned int HP1,float *dir,float *posX,float *posY,bool *isFly)
{
    sf::Packet pack;
    socket.send(pack);

    pack>>HP1>>
            posX[0]>>posY[0]>>isFly[0]>>dir[0]>>
            posX[1]>>posY[1]>>isFly[1]>>dir[1]>>
            posX[2]>>posY[2]>>isFly[2]>>dir[2]>>
            posX[3]>>posY[3]>>isFly[3]>>dir[3]>>
            posX[4]>>posY[4]>>isFly[4]>>dir[4]>>
            posX[5]>>posY[5]>>isFly[5]>>dir[5]>>
            posX[6]>>posY[6]>>isFly[6]>>dir[6]>>
            posX[7]>>posY[7]>>isFly[7]>>dir[7]>>
            posX[8]>>posY[8]>>isFly[8]>>dir[8]>>
            posX[9]>>posY[9]>>isFly[9]>>dir[9]>>
            x>>y>>angle;
}
void Network::Update(float x,float y,float angle,unsigned int HP1,float *dir,float *posX,float *posY,bool *isFly,unsigned int HP2)
{

    if(Type==serwer)
    {
        listener.accept(socket);
    }
    Wyslij(x,y,angle,HP1,dir,posX,posY,isFly);
    Odbierz(HP2);
}
