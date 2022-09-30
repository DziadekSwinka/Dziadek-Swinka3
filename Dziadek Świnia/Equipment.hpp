#ifndef EQUIPMENT_HPP_INCLUDED
#define EQUIPMENT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
struct sklep
{
    sf::RectangleShape background;
    sf::Sprite ico[6];
};
class Equipment
{
private:
    sf::Sound main;
    sf::SoundBuffer intro;
    sf::Font OswaldRegular;
    sf::RectangleShape backRect,icon[6],pieniadz_bcg;
    sf::Sprite symbol[6];
    sf::Texture symbol_txt[6];
    sf::Text text[6],pieniadze_tekst;
    sf::RenderWindow &window;
    void ustaw_Text();
    void ustaw_reke();
public:
    sklep Sklep;
    Equipment(sf::RenderWindow &window1);
    unsigned int ammunition;
    unsigned int HP;
    unsigned int pieniadze;
    bool pistolet,karabin,bazooka,uzi;
    short w_rece;
    void Update(bool panelSklep);
};

#endif // EQUIPMENT_HPP_INCLUDED
