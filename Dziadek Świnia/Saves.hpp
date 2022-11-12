#ifndef SAVES_HPP_INCLUDED
#define SAVES_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "Equipment.hpp"
#include "button.hpp"

class Equipment;

class saveList
{
private:
    float stosX,stosY;
    sf::RenderWindow &window;
    sf::RectangleShape rectangle;
public:
    unsigned int LoadList();
    void load(Equipment *Eq,int i);
    void save(Equipment *Eq);
    bool showList;
    saveList(sf::RenderWindow &window1,float stosX,float stosY);
    void Update();
};

#endif // SAVES_HPP_INCLUDED
