#include "Background.hpp"

Background::Background(sf::RenderWindow &window1,std::string sciezka,float x1,std::string budynek1,float x2,std::string budynek2,float x3,std::string budynek3)
    :window(window1)
{
    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    text.setFont(OswaldRegular);
    text.setCharacterSize(20);
    text.setColor(sf::Color(25,60,210));
    b1_x=x1;
    b2_x=x2;
    b3_x=x3;
    txt.loadFromFile(sciezka);
    b1.loadFromFile(budynek1);
    B1.setTexture(b1);
    B1.setScale(0.5,0.5);
    B1.setOrigin(0,b1.getSize().y);
    b2.loadFromFile(budynek2);
    B2.setTexture(b2);
    B2.setScale(0.5,0.5);
    B2.setOrigin(0,b2.getSize().y);
    b3.loadFromFile(budynek3);
    B3.setTexture(b3);
    B3.setScale(0.5,0.5);
    B3.setOrigin(0,b3.getSize().y);
    for(int i=0;i<3;i++)
    {
        bcg[i].setTexture(txt);
        bcg[i].setScale(2,2);

    }
    bcg[0].setPosition(0-798,window.getSize().y-(txt.getSize().y*1.7));
    bcg[1].setPosition(0,window.getSize().y-(txt.getSize().y*1.7));
    bcg[2].setPosition(window.getSize().x-4,window.getSize().y-(txt.getSize().y*1.7));

}
void Background::wyswietl_napis(float z1,float z2,float z3)
{
    text.setString("Wejdz do budynku \n \t\t[F]");
    text.setPosition(960,400);
    if(abs(x+z1-700)<200)
    {

        pokaz_tekst[0]=1;
    }else pokaz_tekst[0]=0;

    if(abs(x+z3-700)<200)
    {
        pokaz_tekst[1]=1;
    }else pokaz_tekst[1]=0;

    if(abs(x+z2-700)<200)
    {
        pokaz_tekst[2]=1;
    }else pokaz_tekst[2]=0;
}
void Background::Update(Interior interior,unsigned short level)
{
    wyswietl_napis(b1_x,b2_x,b3_x);
    if(interior==outside)
    {
        B1.setPosition(x-b1_x,750);
        B2.setPosition(x-b2_x,750);
        B3.setPosition(x-b3_x,750);
        for(short i=0;i<3;i++)
            bcg[i].setTexture(txt);
    }
    window.draw(B1);
    window.draw(B2);
    window.draw(B3);
    window.draw(bcg[0]);
    window.draw(bcg[1]);
    window.draw(bcg[2]);
    if(true==sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        background_move(Right);
    if(true==sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        background_move(Left);
    if(pokaz_tekst[0]||pokaz_tekst[1]||pokaz_tekst[2])
        if(level<1)
            window.draw(text);
}

bool Background::background_move(side Side)
{
    for(int i=0;i<3;i++)
    {
        if(Side==Left)
        {
            bcg[i].move(0.2,0);
            x+=0.2;
        }
        if(Side==Right)
        {
            bcg[i].move(-0.2,0);
            x-=0.2;
        }

    }
    if((bcg[2].getPosition().x)<0)
        {
            bcg[0].setPosition(0-798,window.getSize().y-(txt.getSize().y*1.7));
            bcg[1].setPosition(0,window.getSize().y-(txt.getSize().y*1.7));
            bcg[2].setPosition(window.getSize().x-4,window.getSize().y-(txt.getSize().y*1.7));
        }
    if((bcg[0].getPosition().x)>0)
        {
            bcg[0].setPosition(0-798,window.getSize().y-(txt.getSize().y*1.7));
            bcg[1].setPosition(0,window.getSize().y-(txt.getSize().y*1.7));
            bcg[2].setPosition(window.getSize().x-4,window.getSize().y-(txt.getSize().y*1.7));
        }

    return true;
}
