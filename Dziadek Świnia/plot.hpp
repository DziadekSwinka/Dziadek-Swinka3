#ifndef PLOT_HPP_INCLUDED
#define PLOT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Plot
{
private:
    sf::RenderWindow &window;
    unsigned int state;
    int &money;
    int extraMoney[8]={20,40,60,65,70,75,80,80};
    void Push_state()
    {
        state++;
        money+=extraMoney[state];

    }
public:
    void Update()
    {
        if(false)   //dorobic warunek ukonczenia stanu
        {
            Push_state();
        }
    }
    Plot(sf::RenderWindow &window1,int &money_temp):window(window1),money(money_temp)
    {
        state=0;
    }
};

#endif // PLOT_HPP_INCLUDED
