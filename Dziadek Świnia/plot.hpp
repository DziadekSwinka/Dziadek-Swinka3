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
    unsigned int * bykHP;
    void Push_state();
    void stateConfig(int nextState);
    void NPC_text(std::string text,float myPosX,float posX);
    struct
    {
        sf::Sprite sprite;
        sf::Texture texture;
        unsigned int appears_drg_st;
        sf::Vector2f position;
    }NPC[6];
    Equipment &Eq;
public:
    unsigned int getState();
    unsigned int *getStateRef();
    int Update(float posX,int bykHP_curr,int UpdateTab[]);
    Plot(sf::RenderWindow &window_temp,Equipment &eq_temp,float Ground_LVL,unsigned int * bykHP_temp);
};

#endif // PLOT_HPP_INCLUDED
