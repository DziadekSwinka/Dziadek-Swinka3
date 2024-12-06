#ifndef PLOT_HPP_INCLUDED
#define PLOT_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Equipment.hpp"
#include "helper.hpp"

class Plot
{
private:
    helper Help;
    sf::Font OswaldRegular;
    sf::RenderWindow &window;
    sf::Text Notification_text;
    unsigned int state;
    //const int number_of_NPCs=1;
//    int &money;
    int extraMoney[8]={20,30,10,10,0,20,30,20};
    void Push_state();
    void NPC_text(std::string text,float myPosX,float posX);
    struct
    {
        sf::Sprite sprite;
        sf::Texture texture;
        unsigned int appears_drg_st;
        sf::Vector2f position;
    }NPC[5];
    Equipment &Eq;
public:
    unsigned int getState();
    int Update(float posX);
    Plot(sf::RenderWindow &window_temp,Equipment &eq_temp,float Ground_LVL);
};

#endif // PLOT_HPP_INCLUDED
