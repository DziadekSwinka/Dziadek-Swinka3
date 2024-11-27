#include "Equipment.hpp"

#include <iostream>

Equipment::Equipment(sf::RenderWindow &window1,float stosX,float stosY,float Vol0,float Vol1):window(window1),stosX(stosX),stosY(stosY)
{
    symbol_txt[0].loadFromFile("Textures//Items//bullet.png");
    symbol_txt[1].loadFromFile("Textures//Items//pistolet.png");
    symbol_txt[2].loadFromFile("Textures//Items//ak47.png");
    symbol_txt[3].loadFromFile("Textures//Items//bazooka.png");
    symbol_txt[4].loadFromFile("Textures//Items//uzi.png");
    symbol_txt[5].loadFromFile("Textures//Items//beer.png");
    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    intro.loadFromFile("Sounds//intro.wav");
    ammunition=15;
    HP=100;
    pieniadze=100;
    beer=0;
    for(int i=0;i<6;i++)
    {
        text[i].setFont(OswaldRegular);
        symbol[i].setTexture(symbol_txt[i]);
        symbol[i].setPosition((70*i+53)/stosX,30/stosY);
        text[i].setPosition((68*i+38)/stosX,98/stosY);
        text[i].setCharacterSize(30/stosX);
    }
    text[5].setPosition((68*5+28)/stosX,98/stosY);
    pistolet=false;
    karabin=false;
    uzi=false;
    bazooka=false;
    w_rece=0;
    dodaj_pieniadze.setFont(OswaldRegular);
    pieniadze_tekst.setFont(OswaldRegular);
    pieniadze_plus.setFont(OswaldRegular);
    pieniadze_tekst.setColor(sf::Color(5,0,170));
    pieniadze_tekst.setPosition(900.f/stosX,5);
    pieniadze_tekst.setStyle(sf::Text::Bold);
    symbol[0].setScale(0.1/stosX,0.1/stosY);
    symbol[1].setScale(-0.14/stosX,0.14/stosY);
    symbol[2].setScale(-0.07/stosX,0.07/stosY);
    symbol[3].setScale(-0.08/stosX,0.1/stosY);
    symbol[4].setScale(-0.15/stosX,0.15/stosY);
    symbol[5].setScale(-0.12/stosX,0.12/stosY);
    symbol[1].setPosition(170/stosX,-8/stosY);
    symbol[2].setPosition(210/stosX,35/stosY);
    symbol[3].setPosition(290/stosX,25/stosY);
    symbol[4].setPosition(430/stosX,39/stosY);
    symbol[5].setPosition(430/stosX,54/stosY);
    symbol[0].setRotation(45);
    symbol[1].setRotation(-45);
    symbol[2].setRotation(-45);
    symbol[3].setRotation(-45);
    symbol[4].setRotation(0);
    symbol[5].setRotation(45);


    backRect.setSize(sf::Vector2f(426.f/stosX,125.f/stosY));
    backRect.setPosition(10.f/stosX,10.f/stosY);
    backRect.setOutlineColor(sf::Color(135,135,135));
    backRect.setOutlineThickness(10);
    backRect.setFillColor(sf::Color(180,180,180));
    pieniadz_bcg.setSize(sf::Vector2f(920.f/stosX,50.f/stosY));
    pieniadz_bcg.setPosition(500.f/stosX,0);
    pieniadz_bcg.setOutlineColor(sf::Color(135,135,135));
    pieniadz_bcg.setOutlineThickness(5);
    pieniadz_bcg.setFillColor(sf::Color(180,180,180));
    for(int i=0;i<6;i++)
    {
        icon[i].setSize(sf::Vector2f(50.f/stosX,50.f/stosY));
        icon[i].setFillColor(sf::Color(220,220,220));
        icon[i].setOutlineColor(sf::Color(135,135,135));
        icon[i].setOutlineThickness(5);
        icon[i].setPosition((70*i+25)/stosX,45.f/stosY);
    }
    ustaw_sklep();
    main.setBuffer(intro);
    main.setVolume(Vol0*Vol1/100);
    main.setLoop(true);
    main.play();

    Ile=0;
    ustaw_Text();
}
void Equipment::pociag()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sf::Time time=clock.getElapsedTime();
        if(time.asSeconds()>=1)
        {
            pieniadze+=1;
            clock.restart();
        }
        pieniadze_plus.setString("+ 1$");
        pieniadze_plus.setColor(sf::Color::Yellow);
        pieniadze_plus.setPosition(pieniadze_tekst.getPosition().x+100,pieniadze_tekst.getPosition().y);
        window.draw(pieniadze_plus);
    }
}
void Equipment::ustaw_sklep()
{
    Sklep.background.setSize(sf::Vector2f(1190.f/stosX,790.f/stosY));
    Sklep.background.setFillColor(sf::Color(160,140,80));
    Sklep.background.setOutlineColor(sf::Color(70,70,70));
    Sklep.background.setOutlineThickness(5);
    Sklep.background.setPosition(360.f/stosX,100.f/stosY);
    Sklep.ico[0].setTexture(symbol_txt[1]);
    Sklep.ico[1].setTexture(symbol_txt[2]);
    Sklep.ico[2].setTexture(symbol_txt[3]);
    Sklep.ico[3].setTexture(symbol_txt[4]);
    Sklep.ico[4].setTexture(symbol_txt[0]);
    Sklep.ico[5].setTexture(symbol_txt[5]);
    for(int i=0;i<6;i++)
    {
        Sklep.ico[i].setPosition(800.f/stosX,(140+i*120)/stosY);
        Sklep.ico[i].setScale(-0.4/stosX,0.34/stosY);

    }
    Sklep.ico[4].setScale(-0.25/stosX,0.25/stosY);
    Sklep.ico[4].setPosition(600.f/stosX,(170+5*120)/stosY);
    Sklep.ico[4].setRotation(90);

    Sklep.ico[5].setScale(-0.15/stosX,0.2/stosY);
    Sklep.ico[5].setPosition(530.f/stosX,(170+5*120)/stosY);
}
void Equipment::ustaw_reke()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        if(pistolet)
            w_rece=1;
    }else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        if(karabin)
            w_rece=2;
    }else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        if(bazooka)
            w_rece=3;
    }else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        if(uzi)
            w_rece=4;
    }else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        if(beer>0 && boostHP==0)
        {
            beer--;
            boostHP=100;
        }
    }
}
void Equipment::ustaw_Text()
{
    text[0].setString(std::to_string(ammunition));
    text[1].setString("[1]");
    text[2].setString("[2]");
    text[3].setString("[3]");
    text[4].setString("[4]");
    text[5].setString(std::to_string(beer)+" [5]");
    for(short i=0;i<6;i++)
    {
        Sklep.price_text[i].setFont(OswaldRegular);
        Sklep.price_text[i].setColor(sf::Color(250,200,60));
        Sklep.price_text[i].setString(std::to_string(price[i])+"$");
        Sklep.price_text[i].setPosition(800/stosX,(170+i*130)/stosY);
    }
    if(pistolet)
    {
        text[1].setColor(sf::Color::Red);
    }else  text[1].setColor(sf::Color(0,0,0));
    if(karabin)
    {
        text[2].setColor(sf::Color::Red);
    }else  text[2].setColor(sf::Color(0,0,0));
    if(bazooka)
    {
        text[3].setColor(sf::Color::Red);
    }else  text[3].setColor(sf::Color(0,0,0));
    if(uzi)
    {
        text[4].setColor(sf::Color::Red);
    }else  text[4].setColor(sf::Color(0,0,0));
    if(true)
    {
        text[0].setColor(sf::Color(5,0,170));
    }
    if(true)
    {
        text[5].setColor(sf::Color::Red);
    }
}
void Equipment::przyciski()
{
    int i;
    for(i=0;i<7;i++)
    {
        if(kup[i].isPressed())
        {
            if(price[i]<=pieniadze)
            {
                std::cout<<price[i]<<" "<<pieniadze<<" "<<i<<std::endl;
                pieniadze-=price[i];
            }else return;
            break;
        }
    }
    switch(i)
    {
    case 0:
        {
            if(pistolet)
            {
                pieniadze+=price[i];
            }else{
                pistolet=true;
            }
        }
        break;
    case 1:
        {
            if(karabin)
            {
                pieniadze+=price[i];
            }else{
                karabin=true;
            }
        }
        break;
    case 2:
        {
            if(bazooka)
            {
                pieniadze+=price[i];
            }else{
                bazooka=true;
            }
        }
        break;
    case 3:
        {
            if(uzi)
            {
                pieniadze+=price[i];
            }else{
                uzi=true;
            }
        }
        break;
    case 4:
        {
            ammunition+=5;
        }
        break;
    /*case 5:
        {
            if(pistolet)
            {
                pieniadze+=price[i];
            }else{
                pistolet=true;
            }
        }*/
    case 5:
        {
            beer++;
        }
        break;
    default: break;
    }
}
void Equipment::Update(bool panelSklep,bool ButtonPressed)
{
    przyciski();
    ustaw_reke();
    pieniadze_tekst.setString(std::to_string(pieniadze)+" $");
    window.draw(pieniadz_bcg);
    window.draw(pieniadze_tekst);
    window.draw(backRect);
    for(int i=0;i<6;i++)
    {
        window.draw(icon[i]);
        window.draw(text[i]);
        window.draw(symbol[i]);
    }
    if(panelSklep)
    {
        window.draw(Sklep.background);
        for(int i=0;i<6;i++)
        {
            window.draw(Sklep.ico[i]);
            window.draw(Sklep.price_text[i]);
            kup[i].Update(ButtonPressed);
        }
    }

    sf::Time time2=clock2.getElapsedTime();
    if(time2.asSeconds()<2)
    {
            dodaj_pieniadze.setPosition(pieniadze_tekst.getPosition().x+200,pieniadze_tekst.getPosition().y);
            dodaj_pieniadze.setString(std::to_string(Ile)+" $");
            dodaj_pieniadze.setColor(sf::Color::Yellow);
            window.draw(dodaj_pieniadze);
    }
}
void Equipment::dodaj_za_zabojstwo(int ile)
{
    Ile=ile;
    pieniadze+=ile;
    clock2.restart();
}
