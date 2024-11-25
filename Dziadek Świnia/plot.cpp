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
unsigned int Plot::getState()
{
    return state;
}
void Plot::NPC_text(std::string text,float myPosX,float posX)
{
    Notification_text.setString(text);
    Notification_text.setPosition(posX-myPosX,300);
    Notification_text.setCharacterSize(24);
    Notification_text.setFillColor(sf::Color::Red);
    window.draw(Notification_text);
    std::cout<<text<<std::endl;
}
void Plot::Update(float posX)
{
    for(auto i:NPC)
    {
        if(i.appears_drg_st==state)
        {
            switch(state)
            {
            case 0:
                if(abs(posX-i.position.x-(1920/2)<200))
                    NPC_text("PRZESZUKAJ [F]",NPC[0].position.x,posX);
                break;
            default: break;
            }
            i.sprite.setPosition(posX-i.position.x,i.position.y);
            window.draw(i.sprite);
        }
    }
    if(false)   //dorobic warunek ukonczenia stanu
    {
        Push_state();
    }
}
