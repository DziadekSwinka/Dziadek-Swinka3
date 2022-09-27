#include "Equipment.hpp"

Equipment::Equipment(sf::RenderWindow &window1):window(window1)
{
    symbol_txt[0].loadFromFile("Textures//bullet.png");
    symbol_txt[1].loadFromFile("Textures//pistolet.png");
    symbol_txt[2].loadFromFile("Textures//bullet.png");
    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    ammunition=15;
    HP=100;
    pieniadze=100;
    for(int i=0;i<4;i++)
    {
        text[i].setFont(OswaldRegular);
        symbol[i].setTexture(symbol_txt[i]);
        symbol[i].setPosition(70*i+53,30);
        text[i].setPosition(70*i+38,98);
    }
    symbol[0].setScale(0.1,0.1);
    symbol[1].setScale(0.1,0.1);
    symbol[2].setScale(0.1,0.1);
    symbol[0].setRotation(45);
    symbol[1].setRotation(45);
    symbol[2].setRotation(45);
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
}
void Equipment::ustaw_Text()
{
    text[0].setString(std::to_string(ammunition));
}
void Equipment::Update()
{
    ustaw_Text();
    window.draw(pieniadz_bcg);
    window.draw(backRect);
    for(int i=0;i<4;i++)
    {
        window.draw(icon[i]);
        window.draw(text[i]);
        window.draw(symbol[i]);
    }
}

