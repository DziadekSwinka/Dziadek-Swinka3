#ifndef NETWORK_HPP_INCLUDED
#define NETWORK_HPP_INCLUDED

#include <SFML/Network.hpp>

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
public:
    Network();
    void Update();
};

#endif // NETWORK_HPP_INCLUDED
