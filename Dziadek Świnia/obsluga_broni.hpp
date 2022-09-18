#ifndef OBSLUGA_BRONI_HPP_INCLUDED
#define OBSLUGA_BRONI_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include "side.hpp"
class bullet
{
private:
    sf::RenderWindow &window;
    sf::Texture txt;
    sf::Sprite sprite;
public:
    void Update();
    bullet(sf::RenderWindow &window1,std::string sciezka);
    float posX,posY;
    float dir;
    bool fly;
    bool k;
};

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

class bron
{
private:
    sf::RenderWindow &window;
    sf::Texture txt;
    sf::Sprite sprite;
    void move_to_side(side Side);
    void wystrzel(float degree);
    bullet Bullet[10] = {   bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                        };
public:
    bron(sf::RenderWindow &window1,std::string sciezka,short bron_type);
    void Update(float posX,float posY,float degree);
};

#endif // OBSLUGA_BRONI_HPP_INCLUDED
