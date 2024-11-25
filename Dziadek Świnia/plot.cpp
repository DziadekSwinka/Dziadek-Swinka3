#include "plot.hpp"

Plot::Plot(sf::RenderWindow &window1,int &money_temp,float Ground_LVL):window(window1),money(money_temp)
{
    state=0;
    NPC[0].texture.loadFromFile("Textures//Charakters//plot1.png");
    NPC[0].appears_drg_st=0;
    NPC[0].position={1500,Ground_LVL-100};
    NPC[0].sprite.setScale(0.5,0.5);
    NPC[0].sprite.setTexture(NPC[0].texture);
}

void Plot::Push_state()
{
    money+=extraMoney[state];
    state++;
}

void Plot::Update(float posX)
{
    for(auto i:NPC)
    {
        if(i.appears_drg_st==state)
        {
            i.sprite.setPosition(posX-i.position.x,i.position.y);
            window.draw(i.sprite);
        }
    }
    if(false)   //dorobic warunek ukonczenia stanu
    {
        Push_state();
    }
}
