#ifndef PLOT_HPP_INCLUDED
#define PLOT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Plot
{
private:
    sf::RenderWindow &window;
    unsigned int state;
    //const int number_of_NPCs=1;
    int &money;
    int extraMoney[8]={20,40,60,65,70,75,80,80};
    void Push_state();
    struct
    {
        sf::Sprite sprite;
        sf::Texture texture;
        unsigned int appears_drg_st;
        sf::Vector2f position;
    }NPC[1];
public:
    void Update(float posX);
    Plot(sf::RenderWindow &window1,int &money_temp, float Ground_LVL);
};

#endif // PLOT_HPP_INCLUDED
