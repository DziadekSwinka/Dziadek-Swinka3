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
    void Wyslij(Postac &postac,float x,unsigned int HP1,bron *Bron);
    void Odbierz(AI &przeciwnik,unsigned int HP2);
public:
    Network();
    ~Network();
    void Update(Postac &postac,AI &przeciwnik,float x,unsigned int HP1,unsigned int HP2,bron *Bron);
};

#endif // NETWORK_HPP_INCLUDED
