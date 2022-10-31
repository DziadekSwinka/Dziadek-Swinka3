#include <fstream>
#include <string>
#include <iostream>

#include "Network.hpp"

Network::Network()
{
    isConnect=false;
    system("cls");
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
            Type=klient;
            throw std::runtime_error ("Zly tekst pliku");
        }
        if(Type==klient)
        {
            std::string ip;
            getline(file,ip);
            IP=static_cast<sf::IpAddress>(ip);
            if(socket.connect(IP,port)!=sf::Socket::Done){
                throw std::runtime_error ("Nie udalo sie polaczyc z "+IP.toString());
            }
            else
            {
                isConnect=true;
            }
        }
        if(Type==serwer)
        {
            if(listener.listen(port)!=sf::Socket::Done){
                throw std::runtime_error("Nie moge rozpoczac nasluchiwania na porcie "+std::to_string(port));
            }
        }
    }else
    {
        throw std::runtime_error ("Nie mozna otworzyc pliku");
    }
    std::cout<<"Moj IP: "<<sf::IpAddress::getLocalAddress()<<std::endl;
    if(Type==serwer)
        std::cout<<"Port: "<<socket.getLocalPort()<<std::endl;
}

Network::~Network()
{
    //socket.close();
}
void Network::Odbierz()
{
    sf::Packet pack;
    socket.receive(pack);
    bool s;
    pack>>HP2>>
            newPosX[0]>>newPosY[0]>>newIsFly[0]>>newDir[0]>>
            newPosX[1]>>newPosY[1]>>newIsFly[1]>>newDir[1]>>
            newPosX[2]>>newPosY[2]>>newIsFly[2]>>newDir[2]>>
            newPosX[3]>>newPosY[3]>>newIsFly[3]>>newDir[3]>>
            newPosX[4]>>newPosY[4]>>newIsFly[4]>>newDir[4]>>
            newPosX[5]>>newPosY[5]>>newIsFly[5]>>newDir[5]>>
            newPosX[6]>>newPosY[6]>>newIsFly[6]>>newDir[6]>>
            newPosX[7]>>newPosY[7]>>newIsFly[7]>>newDir[7]>>
            newPosX[8]>>newPosY[8]>>newIsFly[8]>>newDir[8]>>
            newPosX[9]>>newPosY[9]>>newIsFly[9]>>newDir[9]>>
            newX>>newY>>newAngle>>s;

    if(s==1)
        newSide=Left;
    else if(s==0)
        newSide=Right;
}
void Network::Wyslij(float x,float y,float angle,unsigned int HP1,float *dir,float *posX,float *posY,bool *isFly,side Side)
{
    sf::Packet pack;
    socket.send(pack);
    bool s;
    if(Side==Left)
        s=1;
    else if(Side==Right)
        s=0;
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
            x>>y>>angle>>s;
}
void Network::Update(float x,float y,float angle,unsigned int HP1,float *dir,float *posX,float *posY,bool *isFly,side Side)
{
    if(Type==serwer)
    {
        /*sel.add(listener);
        sel.wait(sf::milliseconds(250));*/
        listener.accept(socket);
    }
    Wyslij(x,y,angle,HP1,dir,posX,posY,isFly,Side);
    Odbierz();
}
