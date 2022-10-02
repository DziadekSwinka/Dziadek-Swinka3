#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <String>
#include <iostream>
#include <math.h>
#include "side.hpp"
#include "mode.hpp"

class Background
{
private:
    sf::RenderWindow &window;
    sf::Sprite bcg[3],B1,B2,B3;
    sf::Texture txt,b1,b2,b3;
    sf::Texture gertruda,chmura;
    sf::Sprite Pociag,Chmura;
    sf::Text text;
    sf::Font OswaldRegular;
    bool background_move(side Side);
    void wyswietl_napis(float z1,float z2,float z3);
    void wejdz(Interior *interior);
    float b1_x,b2_x,b3_x;
    float x=0;
    float x_outside=0;
    bool pokaz_tekst[3]={0,0,0};
public:
    void Update(Interior *interior,unsigned short level);
    Background(sf::RenderWindow &window1,std::string sciezka,float x1,std::string budynek1,float x2,std::string budynek2,float x3,std::string budynek3);
};




#endif // BACKGROUND_HPP_INCLUDED
