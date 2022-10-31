#ifndef NETWORK_HPP_INCLUDED
#define NETWORK_HPP_INCLUDED

#include <SFML/Network.hpp>

#include "Equipment.hpp"
#include "side.hpp"

class Network
{
private:
    enum
    {
        klient,
        serwer
    }Type;

    sf::IpAddress IP;
    sf::TcpListener listener;
    sf::TcpSocket socket;
    sf::SocketSelector sel;
    unsigned int port=54000;
    void Wyslij(float x,float y,float angle,unsigned int HP1,float *dir,float *posX,float *posY,bool *isFly,side Side);
    void Odbierz();
public:
    float newPosX[10];
    float newPosY[10];
    float newDir[10];
    bool newIsFly[10];
    bool isConnect;
    float newAngle;
    unsigned int HP2;
    float newX,newY;
    side newSide;

    Network();
    ~Network();
    void Update(float x,float y,float angle,unsigned int HP1,float *dir,float *posX,float *posY,bool *isFly,side Side);
};

#endif // NETWORK_HPP_INCLUDED
