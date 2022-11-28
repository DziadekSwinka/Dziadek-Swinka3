#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <String>
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <time.h>
#include "side.hpp"
#include "mode.hpp"

float czas_na_klatke();

struct mGraStruct
{
    double speed=1;
    sf::Texture texture;
    sf::Sprite target[5];
    sf::Clock clock;
    sf::Time time;
    sf::Vector2f target_pos[5];
    bool display[5];
};

class Background
{
private:
    sf::RenderWindow &window;
    sf::Sprite bcg[3],B1,B2,B3;
    sf::Texture txt,b1,b2,b3,baza;
    sf::Texture gertruda,chmura,wsk,snieg;
    sf::Sprite Pociag,Chmura,Baza,Wskaznik,Snieg[100];
    sf::Text text;
    sf::Font OswaldRegular;
    bool background_move(side Side);
    void wyswietl_napis(float z1,float z2,float z3);
    void wejdz(Interior *interior,bool *panelSklep);
    unsigned int miniGra();
    float b1_x,b2_x,b3_x;
    float stosX,stosY;
    float x_outside=0;
    bool pokaz_tekst[3]={0,0,0};
    bool mGra=false;
    sf::RectangleShape tloGra;
    mGraStruct mStruct;
    bool snowFall;
    void renderSnow(float deltaTime);
public:
    float x=0;
    unsigned int Update(Interior *interior,unsigned short level,bool *panelSklep,bool EnterPressed,float deltaTime);
    Background(sf::RenderWindow &window1,std::string sciezka,float x1,std::string budynek1,float x2,std::string budynek2,float x3,std::string budynek3,float stosX,float stosY,std::string sezon);
};




#endif // BACKGROUND_HPP_INCLUDED
