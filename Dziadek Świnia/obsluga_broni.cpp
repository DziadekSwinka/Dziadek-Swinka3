#include <math.h>
#include <iostream>
#include "obsluga_broni.hpp"

bullet::bullet(sf::RenderWindow &window1,std::string sciezka):window(window1)
{
    txt.loadFromFile(sciezka);
    sprite.setTexture(txt);
    sprite.setScale(0.05,0.05);
    fly=false;
}
bool bullet::pozaEkranem()
{
    if(posX<0 || posY<0 || posX>window.getSize().x || posY>window.getSize().y )
    {
        return true;
    }

    else return false;
}
void bullet::setPosition(float posX, float posY)
{
    sprite.setPosition(posX,posY);
}
void bullet::setRotation(float dir)
{
    sprite.setRotation(-dir+90);
}
void bullet::Update()
{
    posX=sprite.getPosition().x;
    posY=sprite.getPosition().y;
    float alfa;
    float a,b,c=0.1;
    alfa=sprite.getRotation()+90;
    alfa=alfa/60;         //+270
    a=c*(sin(alfa));
    b=c*(cos(alfa));
    if(k)
        sprite.move(b,a);
    if(!k)
        sprite.move(-b,-a);
    if(pozaEkranem())
        fly=false;

    window.draw(sprite);
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

bron::bron(sf::RenderWindow &window1,std::string sciezka,short bron_type):window(window1)
{
    txt.loadFromFile(sciezka);
    sprite.setTexture(txt);
    sprite.setScale(-0.3,0.3);
    sprite.setOrigin(700,250);
    sprite.setRotation(0);

}
void bron::wystrzel(float degree)
{
    short i=0;
    while(i<10)
    {
        if(Bullet[i].fly==false)
        {
            Bullet[i].fly=true;
            ustawPocisk(i,degree);
        }
        else
            i++;
    }
}
void bron::ustawPocisk(short i,float degree)
{
    Bullet[i].setPosition(sprite.getPosition().x,sprite.getPosition().y);
    Bullet[i].setRotation(degree);
}
void bron::move_to_side(side Side)
{
    if(Side==Right)
    {
        sprite.setScale(-0.3,sprite.getScale().y);
    }else if(Side==Left)
    {
        sprite.setScale(0.3,sprite.getScale().y);
    }
}
void bron::Update(float posX,float posY,float degree)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move_to_side(Right);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move_to_side(Left);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        wystrzel(degree);
    }
    if(sprite.getScale().x>0)
    {
        sprite.setPosition(posX-150,posY+70);
        sprite.setRotation(degree);
    }else
    {
        sprite.setPosition(posX+150,posY+70);
        sprite.setRotation(degree*-1);
    }
    for(short i=0;i<10;i++)
    {
        if(Bullet[i].fly==true)
            Bullet[i].Update();
    }
    window.draw(sprite);
}

/*
float alfa;
        float a,b,c=1;
        alfa=sprite.getRotation()+90;
        alfa=alfa/60;         //+270
        a=c*(sin(alfa));
        b=c*(cos(alfa));
        if(k)
            sprite.move(b,a);
        if(!k)
            sprite.move(-b,-a);
*/
