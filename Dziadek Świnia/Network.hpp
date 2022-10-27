#ifndef NETWORK_HPP_INCLUDED
#define NETWORK_HPP_INCLUDED

#include <SFML/Network.hpp>

#include "Equipment.hpp"
class Equipment;
class Postac;
class AI;
class bron;
struct AI_Eq;

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
    unsigned int port=54000;
    void Wyslij(float x,float y,float angle,unsigned int HP1,float *dir,float *posX,float *posY,bool *isFly);
    void Odbierz(unsigned int HP2);
public:
    Network();
    ~Network();
    void Update(float x,float y,float angle,unsigned int HP1,float *dir,float *posX,float *posY,bool *isFly,unsigned int HP2);
};

#endif // NETWORK_HPP_INCLUDED
