#ifndef EQUIPMENT_HPP_INCLUDED
#define EQUIPMENT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "button.hpp"

const unsigned int price[6]={80,300,500,150,10,100};
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
    sf::RenderWindow &window;
    sf::Sound main;
    sf::SoundBuffer intro;
    sf::Font OswaldRegular;
    sf::RectangleShape backRect,icon[6],pieniadz_bcg;
    sf::Sprite symbol[6];
    sf::Texture symbol_txt[6];
    sf::Text text[6],pieniadze_tekst;
    void ustaw_Text();
    void ustaw_reke();
    void ustaw_sklep();
    void przyciski();
    button kup[6]={ button(window,"Textures//kup.png","Textures//kupc.png",1200,pierwszy_kup),
                    button(window,"Textures//kup.png","Textures//kupc.png",1200,pierwszy_kup+130),
                    button(window,"Textures//kup.png","Textures//kupc.png",1200,pierwszy_kup+260),
                    button(window,"Textures//kup.png","Textures//kupc.png",1200,pierwszy_kup+390),
                    button(window,"Textures//kup.png","Textures//kupc.png",1200,pierwszy_kup+520),
                    button(window,"Textures//kup.png","Textures//kupc.png",1200,pierwszy_kup+650)};
public:
    sklep Sklep;
    Equipment(sf::RenderWindow &window1);
    unsigned int ammunition;
    unsigned int HP;
    unsigned int pieniadze;
    bool pistolet,karabin,bazooka,uzi;
    short w_rece;
    void Update(bool panelSklep,bool ButtonPressed);
};

#endif // EQUIPMENT_HPP_INCLUDED
