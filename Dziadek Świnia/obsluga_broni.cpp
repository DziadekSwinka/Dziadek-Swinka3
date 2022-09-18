#include <math.h>
#include "obsluga_broni.hpp"

bullet::bullet(sf::RenderWindow &window1,std::string sciezka):window(window1)
{
    txt.loadFromFile(sciezka);
    sprite.setTexture(txt);
    sprite.setScale(0.05,0.05);
    fly=false;
}
void bullet::Update()
{
    sprite.setPosition(posX,posY);
    if(fly=true)
    {
        float alfa;
        float a,b,c=3;
        alfa=dir-90;
        alfa=alfa/60;         //+270
        a=c*(sin(alfa));
        b=c*(cos(alfa));
        if(k)
            sprite.move(b,a);
        if(!k)
            sprite.move(-b,-a);
        window.draw(sprite);
    }
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
    for(short i=0;i<10;i++)
    {
        if(!Bullet[i].fly)
        {
            Bullet[i].fly=true;
            Bullet[i].dir=degree;
            Bullet[i].posX=sprite.getPosition().x;
            Bullet[i].posY=sprite.getPosition().y;
            if(sprite.getScale().x>0)
            {
                Bullet[i].k=true;
            }else Bullet[i].k=false;
            break;
        }else{ continue; }
    }
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
        Bullet[i].Update();
    }
    window.draw(sprite);
}
