#include "Equipment.hpp"

Equipment::Equipment(sf::RenderWindow &window1):window(window1)
{
    symbol_txt[0].loadFromFile("Textures//bullet.png");
    symbol_txt[1].loadFromFile("Textures//pistolet.png");
    symbol_txt[2].loadFromFile("Textures//ak47.png");
    symbol_txt[3].loadFromFile("Textures//bazooka.png");
    symbol_txt[4].loadFromFile("Textures//uzi.png");
    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    intro.loadFromFile("Sounds//intro.wav");
    ammunition=15;
    HP=100;
    pieniadze=100;
    for(int i=0;i<6;i++)
    {
        text[i].setFont(OswaldRegular);
        symbol[i].setTexture(symbol_txt[i]);
        symbol[i].setPosition(70*i+53,30);
        text[i].setPosition(68*i+38,98);
    }
    pistolet=false;
    karabin=true;
    uzi=false;
    bazooka=false;
    w_rece=1;
    pieniadze_tekst.setFont(OswaldRegular);
    pieniadze_tekst.setColor(sf::Color(5,0,170));
    pieniadze_tekst.setPosition(900,5);
    pieniadze_tekst.setStyle(sf::Text::Bold);
    symbol[0].setScale(0.1,0.1);
    symbol[1].setScale(-0.14,0.14);
    symbol[2].setScale(-0.07,0.07);
    symbol[3].setScale(-0.08,0.1);
    symbol[4].setScale(-0.15,0.15);
    symbol[1].setPosition(170,-8);
    symbol[2].setPosition(210,35);
    symbol[3].setPosition(290,25);
    symbol[4].setPosition(430,39);
    symbol[0].setRotation(45);
    symbol[1].setRotation(-45);
    symbol[2].setRotation(-45);
    symbol[3].setRotation(-45);
    symbol[4].setRotation(0);

    Sklep.background.setSize(sf::Vector2f(1190,790));
    Sklep.background.setFillColor(sf::Color(160,140,80));
    Sklep.background.setOutlineColor(sf::Color(70,70,70));
    Sklep.background.setOutlineThickness(5);
    Sklep.background.setPosition(360,100);
    Sklep.ico[0].setTexture(symbol_txt[1]);
    Sklep.ico[1].setTexture(symbol_txt[2]);
    Sklep.ico[2].setTexture(symbol_txt[3]);
    Sklep.ico[3].setTexture(symbol_txt[4]);
    Sklep.ico[4].setTexture(symbol_txt[0]);
    for(int i=0;i<6;i++)
    {
        Sklep.ico[i].setPosition(800,140+i*120);
        Sklep.ico[i].setScale(-0.4,0.34);

    }
    Sklep.ico[4].setScale(-0.25,0.25);
    Sklep.ico[4].setPosition(600,140+5*120);
    Sklep.ico[4].setRotation(90);

    backRect.setSize(sf::Vector2f(426,125));
    backRect.setPosition(10,10);
    backRect.setOutlineColor(sf::Color(135,135,135));
    backRect.setOutlineThickness(10);
    backRect.setFillColor(sf::Color(180,180,180));
    pieniadz_bcg.setSize(sf::Vector2f(920,50));
    pieniadz_bcg.setPosition(500,0);
    pieniadz_bcg.setOutlineColor(sf::Color(135,135,135));
    pieniadz_bcg.setOutlineThickness(5);
    pieniadz_bcg.setFillColor(sf::Color(180,180,180));
    for(int i=0;i<6;i++)
    {
        icon[i].setSize(sf::Vector2f(50,50));
        icon[i].setFillColor(sf::Color(220,220,220));
        icon[i].setOutlineColor(sf::Color(135,135,135));
        icon[i].setOutlineThickness(5);
        icon[i].setPosition(70*i+25,45);
    }
    main.setBuffer(intro);
    main.setVolume(40);
    main.setLoop(true);
    main.play();
}
void Equipment::ustaw_reke()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        w_rece=1;
    }else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        w_rece=2;
    }else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        w_rece=3;
    }else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        w_rece=4;
    }else
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        w_rece=5;
    }
}
void Equipment::ustaw_Text()
{
    text[0].setString(std::to_string(ammunition));
    text[1].setString("[1]");
    text[2].setString("[2]");
    text[3].setString("[3]");
    text[4].setString("[4]");
    text[5].setString("[5]");
    for(short i=0;i<6;i++)
    {
        Sklep.price_text[i].setFont(OswaldRegular);
        Sklep.price_text[i].setColor(sf::Color(250,200,60));
        Sklep.price_text[i].setString(std::to_string(price[i])+"$");
        Sklep.price_text[i].setPosition(800,170+i*130);
    }
    if(pistolet)
    {
        text[1].setColor(sf::Color(5,0,170));
    }else  text[1].setColor(sf::Color(0,0,0));
    if(karabin)
    {
        text[2].setColor(sf::Color(5,0,170));
    }else  text[2].setColor(sf::Color(0,0,0));
    if(uzi)
    {
        text[3].setColor(sf::Color(5,0,170));
    }else  text[3].setColor(sf::Color(0,0,0));
    if(bazooka)
    {
        text[4].setColor(sf::Color(5,0,170));
    }else  text[4].setColor(sf::Color(0,0,0));
    if(true)
    {
        text[0].setColor(sf::Color(5,0,170));
    }
}
void Equipment::Update(bool panelSklep)
{
    ustaw_Text();
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
        }
    }
}

