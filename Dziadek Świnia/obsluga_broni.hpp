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
    bool pozaEkranem();
    bullet(sf::RenderWindow &window1,std::string sciezka);
    void setPosition(float posX, float posY);
    void setRotation(float dir);
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
    void wystrzel(float degreee);
    void ustawPocisk(short i,float degre);
    bullet Bullet[10] = {   bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png"),
                            bullet(window,"Textures//bullet.png")};
public:
    bron(sf::RenderWindow &window1,std::string sciezka,short bron_type);
    void Update(float posX,float posY,float degree,bool *EnterP);
};

#endif // OBSLUGA_BRONI_HPP_INCLUDED
