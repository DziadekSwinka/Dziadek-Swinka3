#ifndef EQUIPMENT_HPP_INCLUDED
#define EQUIPMENT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Equipment
{
private:
    sf::Font OswaldRegular;
    sf::RectangleShape backRect,icon[4],pieniadz_bcg;
    sf::Sprite symbol[4];
    sf::Texture symbol_txt[4];
    sf::Text text[4],pieniadze_tekst;
    sf::RenderWindow &window;
    void ustaw_Text();
public:
    Equipment(sf::RenderWindow &window1);
    unsigned int ammunition;
    unsigned int HP;
    unsigned int pieniadze;
    void Update();
};

#endif // EQUIPMENT_HPP_INCLUDED
