#include "plot.hpp"

Plot::Plot(sf::RenderWindow &window_temp,Equipment &eq_temp,float Ground_LVL,unsigned int * bykHP_temp):window(window_temp),Eq(eq_temp),Help(window_temp),bykHP(bykHP_temp)
{
    //*bykHP=*bykHP_temp;
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

    NPC[3].appears_drg_st=3;
    NPC[3].position={500,Ground_LVL-50};
    NPC[3].sprite.setScale(0.5,0.5);
    NPC[3].sprite.setTexture(NPC[2].texture);

    NPC[4].texture.loadFromFile("Textures//Charakters//DannyPies.png");
    NPC[4].appears_drg_st=4;
    NPC[4].position={2500,Ground_LVL-50};
    NPC[4].sprite.setScale(0.4,0.4);
    NPC[4].sprite.setTexture(NPC[4].texture);

    NPC[5].appears_drg_st=5;

    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    Notification_text.setFont(OswaldRegular);
    Notification_text.setCharacterSize(24);
    Notification_text.setFillColor(sf::Color::Red);
}

void Plot::Push_state()
{
    Eq.pieniadze+=extraMoney[state];
    state++;
    stateConfig(state);
}
unsigned int Plot::getState()
{
    return state;
}
unsigned int* Plot::getStateRef()
{
    return &state;
}
void Plot::NPC_text(std::string text,float myPosX,float posX)
{
    Notification_text.setPosition(posX-myPosX,300);
    Notification_text.setString(text);
    window.draw(Notification_text);
    //std::cout<<text<<std::endl;
}
void Plot::stateConfig(int nextState)
{
    if(nextState==5)
        *bykHP=100;
}
int Plot::Update(float posX,int bykHP_curr,int UpdateTab[])
{
    for(int i=0;i<1;i++)
        UpdateTab[i]=0;
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
                        /*if(Help.isSet==false)*/       //nie ma zrobionej kolejki [nie prawda- kolejka juz zrobiona]
                            Help.SetState(3);
                        Eq.ammunition+=20;
                        Push_state();
                    }
                }
                i.sprite.setPosition(posX-i.position.x,i.position.y);
                window.draw(i.sprite);
                break;
            }
            case 2:
            case 3:
            {
                if(abs(posX-i.position.x-(1920/2)+100)<300)
                {
                    //if(Help.isSet==false)
                        //Help.SetState(1);
                    NPC_text("PRZESZUKAJ [F]",NPC[state].position.x,posX);
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                    {
                        if(state==2)
                            Eq.pieniadze+=15;
                        if(state==3 && !Eq.klucz)
                        {
                            Eq.klucz=true;
                            Help.SetState(4);
                        }
                        Push_state();
                    }
                }
                i.sprite.setPosition(posX-i.position.x,i.position.y);
                window.draw(i.sprite);
                break;

            }
            case 4:
            {
                if(abs(posX-i.position.x-(1920/2)+100)<300)
                {
                    if(Help.isSet==false)
                            Help.SetState(5);
                    NPC_text("Porozmawiaj za 100$ [F]",NPC[state].position.x,posX);
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                    {
                        if(Eq.pieniadze>=100)
                        {
                            Eq.pieniadze-=100;
                             Help.SetState(6);
                             Help.SetState(7);
                             Push_state();
                        }
                    }
                }
                i.sprite.setPosition(posX-i.position.x,i.position.y);
                window.draw(i.sprite);
                break;
            }
            case 5:
            {
                Help.SetState(8);
                if(bykHP_curr>0)
                    UpdateTab[0]=1;              //wyciagne Update do main'a a tu zrobie tylko returna z logiki
                else Push_state();
            }
            default:
                {

                break;
                }
            }
        }
        if(/*state>NPC[4].appears_drg_st*/true)
        {
            NPC[4].sprite.setPosition(posX-NPC[4].position.x,NPC[4].position.y);
            window.draw(NPC[4].sprite);
            if(abs(posX-NPC[4].position.x-(1920/2)+100)<300 && NPC[4].appears_drg_st!=state)
                NPC_text("Nie mam nic nowego",NPC[4].position.x,posX);
        }
    }
    Help.Update();
    return (state-1);
}
