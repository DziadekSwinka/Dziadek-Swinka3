#include "plot.hpp"

Plot::Plot(sf::RenderWindow &window_temp,Equipment &eq_temp,float Ground_LVL):window(window_temp),Eq(eq_temp),Help(window_temp)
{
    state=0;

    NPC[0].texture.loadFromFile("Textures//Charakters//plot1.png");
    NPC[0].appears_drg_st=0;
    NPC[0].position={1500,Ground_LVL-100};
    NPC[0].sprite.setScale(0.5,0.5);
    NPC[0].sprite.setTexture(NPC[0].texture);

    NPC[1].texture.loadFromFile("Textures//Charakters//plot2.png");
    NPC[1].appears_drg_st=1;
    NPC[1].position={-1500,Ground_LVL-100};
    NPC[1].sprite.setScale(0.5,0.5);
    NPC[1].sprite.setTexture(NPC[1].texture);

    NPC[2].texture.loadFromFile("Textures//Items//box.png");
    NPC[2].appears_drg_st=2;
    NPC[2].position={-2500,Ground_LVL-50};
    NPC[2].sprite.setScale(0.5,0.5);
    NPC[2].sprite.setTexture(NPC[2].texture);

    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    Notification_text.setFont(OswaldRegular);
    Notification_text.setCharacterSize(24);
    Notification_text.setFillColor(sf::Color::Red);
}

void Plot::Push_state()
{
    Eq.pieniadze+=extraMoney[state];
    state++;
}
unsigned int Plot::getState()
{
    return state;
}
void Plot::NPC_text(std::string text,float myPosX,float posX)
{
    Notification_text.setPosition(posX-myPosX,300);
    Notification_text.setString(text);
    window.draw(Notification_text);

    //std::cout<<text<<std::endl;
}
int Plot::Update(float posX)
{
    for(auto i:NPC)
    {
        if(i.appears_drg_st==state)
        {
            switch(state)
            {
            case 0:
            {
                if(abs(posX-i.position.x-(1920/2)+100)<300)
                {
                    if(Help.isSet==false)
                        Help.SetState(1);
                    NPC_text("PRZESZUKAJ [F]",NPC[0].position.x,posX);
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                    {
                        Eq.pistolet=true;
                        Push_state();
                    }
                }
                i.sprite.setPosition(posX-i.position.x,i.position.y);
                window.draw(i.sprite);
                break;
            }
            case 1:
            {
                if(abs(posX-i.position.x-(1920/2)+100)<300)
                {
                    if(Help.isSet==false)
                        Help.SetState(2);
                    NPC_text("PRZESZUKAJ [F]",NPC[1].position.x,posX);
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                    {
                        /*if(Help.isSet==false)*/       //nie ma zrobionej kolejki
                            Help.SetState(3);
                        Eq.ammunition+=10;
                        Push_state();
                    }
                }
                i.sprite.setPosition(posX-i.position.x,i.position.y);
                window.draw(i.sprite);
                break;
            }
            case 2:
            {
                if(abs(posX-i.position.x-(1920/2)+100)<300)
                {
                    //if(Help.isSet==false)
                        //Help.SetState(1);
                    NPC_text("PRZESZUKAJ [F]",NPC[2].position.x,posX);
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                    {
                        Eq.pieniadze+=15;
                        Push_state();
                    }
                }
                i.sprite.setPosition(posX-i.position.x,i.position.y);
                window.draw(i.sprite);
                break;

            }
            default: break;
            }

        }
    }
    Help.Update();
    return (state-1);
}
