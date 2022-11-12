#ifndef EQUIPMENT_HPP_INCLUDED
#define EQUIPMENT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.hpp"

const unsigned int price[6]={80,300,500,150,10,0};
const float pierwszy_kup = {160.f};

struct sklep
{
    sf::RectangleShape background;
    sf::Sprite ico[6];
    sf::Text price_text[6];

};
class Equipment
{
private:
    friend void save();
    friend void load();
    sf::RenderWindow &window;
    sf::SoundBuffer intro;
    sf::Font OswaldRegular;
    sf::RectangleShape backRect,icon[6],pieniadz_bcg;
    sf::Sprite symbol[6];
    sf::Texture symbol_txt[6];
    sf::Clock clock,clock2;
    sf::Text text[6],pieniadze_tekst,pieniadze_plus,dodaj_pieniadze;
    void ustaw_Text();
    void ustaw_reke();
    void ustaw_sklep();
    void przyciski();
    float stosX,stosY;
    button kup[6]={ button(window,"Textures//GUI//kup.png","Textures//GUI//kupc.png",1200.f*stosX,pierwszy_kup*stosY,stosX,stosY),
                    button(window,"Textures//GUI//kup.png","Textures//GUI//kupc.png",1200.f*stosX,(pierwszy_kup+130)*stosY,stosX,stosY),
                    button(window,"Textures//GUI//kup.png","Textures//GUI//kupc.png",1200.f*stosX,(pierwszy_kup+260)*stosY,stosX,stosY),
                    button(window,"Textures//GUI//kup.png","Textures//GUI//kupc.png",1200.f*stosX,(pierwszy_kup+390)*stosY,stosX,stosY),
                    button(window,"Textures//GUI//kup.png","Textures//GUI//kupc.png",1200.f*stosX,(pierwszy_kup+520)*stosY,stosX,stosY),
                    button(window,"Textures//GUI//kup.png","Textures//GUI//kupc.png",1200.f*stosX,(pierwszy_kup+650)*stosY,stosX,stosY)};
    int Ile;
public:
    sf::Sound main;
    sklep Sklep;
    Equipment(sf::RenderWindow &window1,float stosX,float stosY,float Vol0,float Vol1);
    int ammunition;
    int HP;
    int pieniadze;
    int boostHP;
    bool pistolet,karabin,bazooka,uzi;
    short w_rece;
    void Update(bool panelSklep,bool ButtonPressed);
    void dodaj_za_zabojstwo(int ile);
    void pociag();
};

#endif // EQUIPMENT_HPP_INCLUDED
