#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include "side.hpp"
#include "Equipment.hpp"
#include "level.hpp"


//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

bool ButtonPressed=0;
bool EnterPressed=0;
short level=1;

enum Interior
{
    shop,
    home,
    outside
};
struct obj
{
    sf::Texture txt1,txt2;
    float posX,posY;
    sf::Sprite sprite;
    sf::RectangleShape rect;
    bool active;
    float vs=0;
    unsigned short type;
};
void level_setUp(unsigned short level);
Interior interior;
AI_Eq peppaEq;
obj skrzynka;

class bullet;
bullet* bullet_wsk[10];



//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
class Background
{
private:

    sf::RenderWindow &window;
    sf::Sprite bcg[3],B1,B2,B3;
    sf::Texture txt,b1,b2,b3;
    bool background_move(side Side);
    float b1_x,b2_x,b3_x;
    float x=0;
public:
    void Update();
    Background(sf::RenderWindow &window1,std::string sciezka,float x1,std::string budynek1,float x2,std::string budynek2,float x3,std::string budynek3);
};


Background::Background(sf::RenderWindow &window1,std::string sciezka,float x1,std::string budynek1,float x2,std::string budynek2,float x3,std::string budynek3)
    :window(window1)
{
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
void Background::Update()
{
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
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
class button
{
private:
    sf::RenderWindow &window;
    sf::Texture txt,txt2;
    sf::Sprite Button;
    bool onclick=false;
public:
    button(sf::RenderWindow &window1,std::string sciezka,std::string sciezka2,float x,float y);
    void Update();
    bool isPressed();
};
button::button(sf::RenderWindow &window1,std::string sciezka,std::string sciezka2,float x,float y):window(window1)
{
    txt.loadFromFile(sciezka);
    txt2.loadFromFile(sciezka2);
    Button.setTexture(txt);
    Button.setPosition(x,y);

}
void button::Update()
{
    sf::Vector2i Mouse = sf::Mouse::getPosition( window );
    float szerokosc=txt.getSize().x;
    float wysokosc=txt.getSize().y;
    float x=Button.getPosition().x;
    float y=Button.getPosition().y;
    if((Mouse.x>x)&&(Mouse.x<x+szerokosc)&&(Mouse.y>y)&&(Mouse.y<y+wysokosc))
    {
        Button.setTexture(txt2);
    }else Button.setTexture(txt);
    window.draw(Button);
    if((Mouse.x>x)&&(Mouse.x<x+szerokosc)&&(Mouse.y>y)&&(Mouse.y<y+wysokosc) && ButtonPressed)
    {
        onclick=true;
    }else onclick=false;
}
bool button::isPressed()
{
    if(onclick)
    {
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
class Postac
{
protected:
    sf::RenderWindow &window;
    sf::Texture txt,txt2,red_txt,white_txt;
    sf::Sprite postac,red[10],white;
    void Fall();
    void move_to_side(side Side);
    float vs=0;
    float hand_degree=0;
public:
    Postac(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,float x,float y);
    void getDmg(unsigned int *Hp);
    float getDegree();
    float posX,posY;
    void Update(unsigned int Hp);
};
Postac::Postac(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,float x,float y):window(window1)
{
    red_txt.loadFromFile("Textures//red_.png");
    white_txt.loadFromFile("Textures//white_.png");
    for(int i=0;i<10;i++)
    {
        red[i].setTexture(red_txt);
        red[i].setScale(0.25,0.25);
    }

    white.setTexture(white_txt);
    txt.loadFromFile(sciezka);
    txt2.loadFromFile(sciezka1);
    postac.setTexture(txt);
    postac.setScale(0.5,0.5);
    postac.setOrigin((txt.getSize().x)*postac.getScale().x/2,(txt.getSize().y)*postac.getScale().y/2);
    postac.setPosition(x,y);
    posX=x;
    posY=y;
}
void Postac::getDmg(unsigned int *Hp)
{
    postac.setTexture(txt2);
    if(*Hp>10)
        *Hp-=10;
    postac.setTexture(txt);
}
void Postac::move_to_side(side Side)
{
    if(Side==Right)
    {
        postac.setScale(0.5,postac.getScale().y);
    }else if(Side==Left)
    {
        postac.setScale(-0.5,postac.getScale().y);
    }
}
void Postac::Update(unsigned int Hp)
{
    Fall();

    //postac.setPosition(posX,posY);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move_to_side(Right);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move_to_side(Left);
    }
    posX=postac.getPosition().x;
    posY=postac.getPosition().y;
    if(postac.getScale().x>0)
    {
        white.setPosition(posX-50,posY-100);
        for(int i=0;i<10;i++)
        {
            red[i].setPosition(posX-50+20*i,posY-100);
        }
    }
    else
    {
        white.setPosition(posX-150,posY-100);
        for(int i=0;i<10;i++)
        {
            red[i].setPosition(posX-150+20*i,posY-100);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        hand_degree+=0.2;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        hand_degree-=0.2;
    window.draw(postac);
    window.draw(white);
    Hp/=10;
    for(int i=0;i<Hp;i++)
        window.draw(red[i]);

}
float Postac::getDegree()
{
    return hand_degree;
}
void Postac::Fall()
{
    float gravity=0.0001;
    if(postac.getPosition().y+(txt.getSize().y)/4<=window.getSize().y-380&&postac.getPosition().y>=0+5)
    {
        if(true==sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            vs=-0.1;
            postac.move(0,vs);
        }
        else if(false==sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            vs+=gravity;
            postac.move(0,vs);
        }
    }else if((postac.getPosition().y+(txt.getSize().y)/4)>window.getSize().y-380)
    {
        postac.setPosition(postac.getPosition().x,window.getSize().y-(txt.getSize().y/4)-380);
        vs=0;
    }else if((postac.getPosition().y<5))
    {
        postac.setPosition(postac.getPosition().x,5);
    }
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
class bullet
{
private:
    sf::RenderWindow &window;
    sf::Texture txt;
    sf::Sprite sprite;
public:
    void Update();
    bool pozaEkranem();
    bullet(sf::RenderWindow &window1,std::string sciezka,int i);
    void setPosition(float posX, float posY);
    void setRotation(float dir);
    float posX,posY;
    float dir;
    bool fly;
    bool k;
};
bullet::bullet(sf::RenderWindow &window1,std::string sciezka,int i):window(window1)
{
    txt.loadFromFile(sciezka);
    sprite.setTexture(txt);
    sprite.setScale(0.05,0.05);
    fly=false;
    bullet_wsk[i]=this;
}

bool bullet::pozaEkranem()
{
    if(posX<0 || posY<0 || posX>window.getSize().x || posY>window.getSize().y )
    {
        return true;
    }

    else return false;
}
void bullet::setPosition(float X, float Y)
{
    sprite.setPosition(X,Y);
}
void bullet::setRotation(float dir)
{
    if(!k)
    {
        sprite.setRotation(-dir+90);
        sprite.setScale(0.05,0.05);
    }
    else
    {
         sprite.setRotation(dir-90+180);
         sprite.setScale(-0.05,-0.05);
    }
}

void bullet::Update()
{
    posX=sprite.getPosition().x;
    posY=sprite.getPosition().y;
    float alfa;
    float a,b,c=0.5;
    alfa=sprite.getRotation()+90;
    alfa=alfa/60;         //+270
    a=c*(sin(alfa));
    b=c*(cos(alfa));
    if(k)
        sprite.move(b,a);
    if(!k)
        sprite.move(-b,-a);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite.move(-0.2,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sprite.move(0.2,0);
    }
    if(pozaEkranem())
        fly=false;

    window.draw(sprite);
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

class bron
{
private:
    sf::RenderWindow &window;
    sf::Texture txt;
    sf::Sprite sprite;
    void move_to_side(side Side);
    void wystrzel(float degreee);
    void ustawPocisk(short i,float degre);
public:
    bullet Bullet[10] = {   bullet(window,"Textures//bullet.png",0),
                            bullet(window,"Textures//bullet.png",1),
                            bullet(window,"Textures//bullet.png",2),
                            bullet(window,"Textures//bullet.png",3),
                            bullet(window,"Textures//bullet.png",4),
                            bullet(window,"Textures//bullet.png",5),
                            bullet(window,"Textures//bullet.png",6),
                            bullet(window,"Textures//bullet.png",7),
                            bullet(window,"Textures//bullet.png",8),
                            bullet(window,"Textures//bullet.png",9)};
    bron(sf::RenderWindow &window1,std::string sciezka,short bron_type);
    void Update(float posX,float posY,float degree,bool *EnterP);
};
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
            break;
        }
        else
            i++;
    }
}
void bron::ustawPocisk(short i,float degree)
{
    Bullet[i].setPosition(sprite.getPosition().x,sprite.getPosition().y);
    Bullet[i].setRotation(degree);
    if(sprite.getScale().x>0)
        Bullet[i].k=true;
    else
        Bullet[i].k=false;
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
void bron::Update(float posX,float posY,float degree,bool *EnterP)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        move_to_side(Right);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        move_to_side(Left);
    }
    if(*EnterP==true)
    {
        wystrzel(degree);
        *EnterP=false;
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



//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------






class AI
    :public Postac
{
private:
    sf::Texture b1;
    sf::Texture mieso;
    sf::Sprite B1;
    void ustawBron();
    double odleglosc();
public:
    void Update(unsigned int HP);
    bool dotykaPostaci(int i);
    AI(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka_bron,float x,float y);
};
AI::AI(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka_bron,float x,float y)
    :Postac(window1,sciezka,sciezka1,x,y)
{
    mieso.loadFromFile("Textures//porkchop_raw.png");
    b1.loadFromFile(sciezka_bron);
    B1.setTexture(b1);
    B1.setScale(0.08,0.08);
}
double AI::odleglosc()
{
    double dist;
    dist=abs(posX)+(window.getSize().x/2);
    return dist;
}
void AI::ustawBron()
{
    if(postac.getScale().x>0)
    {
        B1.setPosition(posX+80,670);
        B1.setScale(0.08,0.08);
    }
    else
    {
        B1.setPosition(posX-80,670);
        B1.setScale(-0.08,0.08);
    }

}
bool AI::dotykaPostaci(int i)
{
        float bX=bullet_wsk[i]->posX;
        float bY=bullet_wsk[i]->posY;
        float originX=postac.getOrigin().x;
        float originY=postac.getOrigin().y;
        float x=postac.getPosition().x;
        float y=postac.getPosition().y;
        x-=originX;
        y-=originY;
        float sizeX=txt.getSize().x;
        float sizeY=txt.getSize().y;
        sizeX*=postac.getScale().x;
        sizeY*=postac.getScale().y;
        if((x)>bX && bX>(x-sizeX))
        {
            if((y)<bY && bY<(y+sizeY))
            {
                if(bullet_wsk[i]->fly==true)
                {
                    bullet_wsk[i]->fly=false;
                    return true;
                }else return false;
            }else return false;
        }else return false;
}
void AI::Update(unsigned int Hp)
{
    int przedzial;
    int losowa=std::rand()%2000;
    if(losowa==1)
    {
        move_to_side(Right);
        do
        {
            przedzial=1;
            postac.move(0.8,0);
            przedzial++;
        }while(std::rand()%przedzial==1 && przedzial<=100);
    }
    if(losowa==0)
    {
        move_to_side(Left);
        do
        {
            przedzial=1;
            postac.move(-0.8,0);
            przedzial++;
        }while(std::rand()%przedzial==1 && przedzial<=100);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        postac.move(-0.8,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        postac.move(0.8,0);
    }
    posX=postac.getPosition().x;
    posY=postac.getPosition().y;
    for(int i=0;i<10;i++)
    {
        if(dotykaPostaci(i)==true)
        {
            if(peppaEq.HP>=10)
            {
                peppaEq.HP-=10;
            }
        }
    }

    if(postac.getScale().x>0)
    {
        white.setPosition(posX-50,posY-100);
        for(int i=0;i<10;i++)
        {
            red[i].setPosition(posX-50+20*i,posY-100);
        }
    }
    else
    {
        white.setPosition(posX-150,posY-100);
        for(int i=0;i<10;i++)
        {
            red[i].setPosition(posX-150+20*i,posY-100);
        }
    }
    ustawBron();
    if(false)
        hand_degree+=0.2;
    if(false)
        hand_degree-=0.2;
    if(Hp<=10)
    {
        postac.setTexture(mieso);
    }
    window.draw(postac);
    if(Hp>10)
        window.draw(B1);

    window.draw(white);
    Hp/=10;
    for(int i=0;i<Hp;i++)
        window.draw(red[i]);

}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void losuj_zrzut()
{
    unsigned short l=(std::rand()%8)+1;
    switch (l)
    {
    case 1:
        {
            if(!skrzynka.active)
            {
                skrzynka.active=true;
                skrzynka.posX=(std::rand()%1920);
                skrzynka.rect.setTexture(&skrzynka.txt1);
                skrzynka.posY=0;
                skrzynka.type=1;
            }
            break;
        }
    case 2:
        {
            if(!skrzynka.active)
            {
                skrzynka.active=true;
                skrzynka.posX=(std::rand()%1920);
                skrzynka.rect.setTexture(&skrzynka.txt2);
                skrzynka.posY=0;
                skrzynka.type=2;
            }
            break;
        }
    default: break;
    }
    skrzynka.rect.setPosition(sf::Vector2f(skrzynka.posX,skrzynka.posY));
}
void skrzynka_off(Equipment *Eq)
{
    skrzynka.active=false;
    switch (skrzynka.type)
    {
    case 1:
        if(Eq->HP<50)
            Eq->HP+=50;
        else
            Eq->HP=100;
        break;
    case 2:
        Eq->ammunition+=5;
        break;
    }
    skrzynka.type=0;
}
void skrzynka_fall(int GroundLevel,float x,Equipment *Eq)
{
    skrzynka.posX=skrzynka.rect.getPosition().x;
    skrzynka.posY=skrzynka.rect.getPosition().y;
    if(skrzynka.posY<GroundLevel)
    {
        skrzynka.vs+=0.001;
        skrzynka.rect.move(0,skrzynka.vs);
    }
    if(skrzynka.posY>=GroundLevel)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            skrzynka.rect.move(-0.8,0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            skrzynka.rect.move(0.8,0);
        }
        if(x<skrzynka.posX)
        {
            if(skrzynka.posX-x<10)
                {
                    skrzynka_off(Eq);
                }
        }else if(x-skrzynka.posX<10)
                 {
                     skrzynka_off(Eq);
                 }
    }
}
void skrzynki()
{
    skrzynka.rect.setSize(sf::Vector2f(50,50));
    skrzynka.active=false;
    skrzynka.txt1.loadFromFile("Textures//apteczka.png");
    skrzynka.txt2.loadFromFile("Textures//ammo.png");
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    srand(time(NULL));
    interior=outside;
    bool Menu_misje=false;
    const int GroundLevel=700;
    sf::Clock liczZrzut;

    sf::RenderWindow window(sf::VideoMode(1920,1080), "Dziadek Swinka");
    Postac Dziadek(window,"Textures//dziadek.png","Textures//dziadek_dmg.png",window.getSize().x/2,GroundLevel);
    AI peppa(window,"Textures//obrazek.png","Textures//obrazek_dmg.png","Textures//noz.png",100,GroundLevel-50);
    Background background(window,"Textures//grass.png",100,"Textures//grandpahouse.png",-800,"Textures//house.png",900,"Textures//shop.png");
    button Misje_bt(window,"Textures//bm.png","Textures//bmc.png",900,50);
    button Misja1_bt(window,"Textures//m1.png","Textures//m1c.png",1300,10);
    button Misja2_bt(window,"Textures//m2.png","Textures//m2c.png",1300,110);
    bron karabin(window,"Textures//ak47.png",1);
    Equipment Eq(window);
    skrzynki();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left )
            {
                ButtonPressed=true;
            }else ButtonPressed=false;
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
            {
                if(Eq.ammunition>0)
                {
                    EnterPressed=true;
                    Eq.ammunition--;
                }
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)    ///To jest do wywalenia potem ,teraz  do testów
                Dziadek.getDmg(&Eq.HP);
        }
        sf::Time time1=liczZrzut.getElapsedTime();
        if(time1.asSeconds()>15)
        {
            liczZrzut.restart();
            losuj_zrzut();
        }
        if(Misje_bt.isPressed())
        {
            if(Menu_misje)
            {
                Menu_misje=0;
            }
            else
                if(!Menu_misje)
                    Menu_misje=1;
        }
        if(Misja1_bt.isPressed())
        {
            if(level==0)
            {
                level=1;
                level_setUp(1,&Eq,&peppaEq);
            }
        }
        window.clear(sf::Color(138,191,255));
        background.Update();
        if(skrzynka.active)
        {
            skrzynka_fall(GroundLevel,Dziadek.posX,&Eq);
            window.draw(skrzynka.rect);
        }

        Dziadek.Update(Eq.HP);
        karabin.Update(Dziadek.posX,Dziadek.posY,Dziadek.getDegree(),&EnterPressed);
        if(level==1)
        {
            if(peppaEq.HP>0)
                peppa.Update(peppaEq.HP);
        }

        Eq.Update();
        Misje_bt.Update();
        if(Menu_misje)
        {
            Misja1_bt.Update();
        }
        if(Menu_misje)
        {
            Misja2_bt.Update();
        }

        window.display();
    }
    EnterPressed=false;
    return 0;
}
