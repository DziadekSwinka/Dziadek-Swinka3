#include "Equipment.hpp"

Equipment::Equipment(sf::RenderWindow &window1):window(window1)
{
    symbol_txt[0].loadFromFile("Textures//bullet.png");
    symbol_txt[1].loadFromFile("Textures//pistolet.png");
    symbol_txt[2].loadFromFile("Textures//ak47.png");
    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    intro.loadFromFile("Sounds//intro.wav");
    ammunition=15;
    HP=100;
    pieniadze=100;
    for(int i=0;i<4;i++)
    {
        text[i].setFont(OswaldRegular);
        symbol[i].setTexture(symbol_txt[i]);
        symbol[i].setPosition(70*i+53,30);
        text[i].setPosition(68*i+38,98);
    }
    pistolet=false;
    karabin=true;
    w_rece=1;
    pieniadze_tekst.setFont(OswaldRegular);
    pieniadze_tekst.setColor(sf::Color(5,0,170));
    pieniadze_tekst.setPosition(900,5);
    pieniadze_tekst.setStyle(sf::Text::Bold);
    symbol[0].setScale(0.1,0.1);
    symbol[1].setScale(-0.14,0.14);
    symbol[2].setScale(-0.07,0.07);
    symbol[1].setPosition(170,-8);
    symbol[2].setPosition(210,35);
    symbol[0].setRotation(45);
    symbol[1].setRotation(-45);
    symbol[2].setRotation(-45);

    backRect.setSize(sf::Vector2f(290,125));
    backRect.setPosition(10,10);
    backRect.setOutlineColor(sf::Color(135,135,135));
    backRect.setOutlineThickness(10);
    backRect.setFillColor(sf::Color(180,180,180));
    pieniadz_bcg.setSize(sf::Vector2f(920,50));
    pieniadz_bcg.setPosition(500,0);
    pieniadz_bcg.setOutlineColor(sf::Color(135,135,135));
    pieniadz_bcg.setOutlineThickness(5);
    pieniadz_bcg.setFillColor(sf::Color(180,180,180));
    for(int i=0;i<4;i++)
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
    }
}
void Equipment::ustaw_Text()
{
    text[0].setString(std::to_string(ammunition));
    text[1].setString("[1]");
    text[2].setString("[2]");
    if(pistolet)
    {
        text[1].setColor(sf::Color(5,0,170));
    }
    if(karabin)
    {
        text[2].setColor(sf::Color(5,0,170));
    }
    if(true)
    {
        text[0].setColor(sf::Color(5,0,170));
    }
}
void Equipment::Update()
{
    ustaw_Text();
    ustaw_reke();
    pieniadze_tekst.setString(std::to_string(pieniadze)+" $");
    window.draw(pieniadz_bcg);
    window.draw(pieniadze_tekst);
    window.draw(backRect);
    for(int i=0;i<4;i++)
    {
        window.draw(icon[i]);
        window.draw(text[i]);
        window.draw(symbol[i]);
    }
}

