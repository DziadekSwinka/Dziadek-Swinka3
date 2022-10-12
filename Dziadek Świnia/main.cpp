#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <fstream>
#include "side.hpp"
#include "Equipment.hpp"
#include "level.hpp"
#include "button.hpp"
#include "Background.hpp"
#include "mode.hpp"

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

bool ButtonPressed=0;
bool EnterPressed=0;
bool panelSklep=0;
short level=0;

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
Interior interior=outside;
AI_Eq peppaEq,mamaEq;
obj skrzynka;
sf::Clock klatka;
sf::Time poprz_klatka;

sf::ContextSettings setting;

class bullet;
bullet* bullet_wsk[10]={nullptr};

unsigned int Xokna=1920,Yokna=1080;
float frameLimit=0;



//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
float czas_na_klatke()
{
    const float czasX=600;
    float ret={1.f};
    float uTime=poprz_klatka.asSeconds();
    ret=uTime*czasX;
    return ret;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
class Postac
{
private:
    void graj_dzwiek();
    void graj_dzwiek(unsigned short i);
    float oblicz_czas(int w_rece,float czas);
    sf::Font OswaldRegular;
    sf::Text czas;
protected:
    sf::SoundBuffer buffer1,buffer2,buffer3,buffer4;
    sf::Sound sound;
    sf::RenderWindow &window;
    sf::Texture txt,txt2,red_txt,white_txt;
    sf::Sprite postac,red[10],white;
    void Fall();
    void move_to_side(side Side);
    float vs=0;
    float hand_degree=0;
    float stosX,stosY;
public:
    Postac(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka2,std::string sciezka3,std::string sciezka4,std::string sciezka5,float x,float y,float stosX,float stosY);
    void getDmg(unsigned int *Hp);
    float getDegree();
    float posX,posY;
    void Update(unsigned int Hp,sf::Time czas_p,int w_rece);
};
Postac::Postac(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka2,std::string sciezka3,std::string sciezka4,std::string sciezka5,float x,float y,float stosX,float stosY):window(window1),stosX(stosX),stosY(stosY)
{
    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    red_txt.loadFromFile("Textures//red_.png");
    white_txt.loadFromFile("Textures//white_.png");
    czas.setFont(OswaldRegular);

    for(int i=0;i<10;i++)
    {
        red[i].setTexture(red_txt);
        red[i].setScale(0.25,0.25);
    }
    buffer1.loadFromFile(sciezka2);
    buffer2.loadFromFile(sciezka3);
    buffer3.loadFromFile(sciezka4);
    buffer4.loadFromFile(sciezka5);
    white.setTexture(white_txt);
    txt.loadFromFile(sciezka);
    txt2.loadFromFile(sciezka1);
    postac.setTexture(txt);
    postac.setScale(0.5/stosX,0.5/stosY);
    postac.setOrigin((txt.getSize().x)*postac.getScale().x/(stosX*2),(txt.getSize().y)*postac.getScale().y/(stosY*2));
    postac.setPosition(x/stosX,y/stosY);
    posX=x;
    posY=y;
}
float Postac::oblicz_czas(int w_rece,float czas)
{
    switch(w_rece)
    {
    case 1:
        {
            if(czas>2)
            {
                return 0;
            }else return (2-czas);
        }
    case 2:
        {
            if(czas>0.3)
            {
                return 0;
            }else return (0.3-czas);
        }
    case 3:
        {
            if(czas>5)
            {
                return 0;
            }else return (5-czas);
        }
    case 4:
        {
            if(czas>0.2)
            {
                return 0;
            }else return (0.2-czas);
        }
    case 5:
        {
            if(czas>1)
            {
                return 0;
            }else return (1-czas);
        }
    default: return(0);
    }
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
        postac.setScale(0.5/stosX,postac.getScale().y);
    }else if(Side==Left)
    {
        postac.setScale(-0.5/stosY,postac.getScale().y);
    }
}

void Postac::graj_dzwiek(unsigned short i)
{
    if(sound.getStatus() == sf::Sound::Playing)
    {
        return;
    }
    switch(i)
    {
    case 1:
        sound.setBuffer(buffer1);
        break;
    case 2:
        sound.setBuffer(buffer2);
        break;
    case 3:
        sound.setBuffer(buffer3);
        break;
    case 4:
        sound.setBuffer(buffer4);
        break;
    }
    sound.play();
}
void Postac::graj_dzwiek()
{
    srand(time(NULL));
    unsigned short i=(std::rand()%5);
    graj_dzwiek(i);
}
void Postac::Update(unsigned int Hp,sf::Time czas_p,int w_rece)
{
    czas.setString(std::to_string(oblicz_czas(w_rece,czas_p.asSeconds())));
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
        czas.setPosition(posX-10,posY-220);
        white.setPosition(posX-50,posY-100);
        for(int i=0;i<10;i++)
        {
            red[i].setPosition(posX-50+20*i,posY-100);
        }
    }
    else
    {
        czas.setPosition(posX-110,posY-220);
        white.setPosition(posX-150,posY-100);
        for(int i=0;i<10;i++)
        {
            red[i].setPosition(posX-150+20*i,posY-100);
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        hand_degree+=0.2*czas_na_klatke();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        hand_degree-=0.2*czas_na_klatke();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        graj_dzwiek();
    }
    window.draw(postac);
    window.draw(white);
    window.draw(czas);
    Hp/=10;
    for(int i=0;static_cast<unsigned int>(i)<Hp;i++)
        window.draw(red[i]);

}
float Postac::getDegree()
{
    return hand_degree;
}
void Postac::Fall()
{
    float gravity=0.0001;
    if(postac.getPosition().y+(txt.getSize().y)/4<=window.getSize().y-380/stosY&&postac.getPosition().y>=0+5)
    {
        if(true==sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            vs=-0.1;
            postac.move(0,vs*czas_na_klatke()*3);
        }
        else if(false==sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            vs+=gravity*czas_na_klatke()*2;
            postac.move(0,vs*czas_na_klatke()*3);
        }
    }else if((postac.getPosition().y+(txt.getSize().y)/4)>window.getSize().y-380.f/stosY)
    {
        postac.setPosition(postac.getPosition().x,window.getSize().y-(txt.getSize().y/4)-380.f/stosY);
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
        sprite.move(b*czas_na_klatke(),a*czas_na_klatke());
    if(!k)
        sprite.move(-b*czas_na_klatke(),-a*czas_na_klatke());
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        sprite.move(-0.2*czas_na_klatke(),0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        sprite.move(0.2*czas_na_klatke(),0);
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
    sf::Texture txt[5];
    sf::RectangleShape sprite;
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
    bron(sf::RenderWindow &window1,std::string sciezka,std::string sciezka2,std::string sciezka3,std::string sciezka4);
    void Update(float posX,float posY,float degree,bool *EnterP,short type);
};
bron::bron(sf::RenderWindow &window1,std::string sciezka,std::string sciezka2,std::string sciezka3,std::string sciezka4):window(window1)
{
    sprite.setSize(sf::Vector2f(1024,370));
    txt[0].loadFromFile(sciezka2);
    txt[2].loadFromFile(sciezka);
    txt[1].loadFromFile(sciezka2);
    txt[3].loadFromFile(sciezka3);
    txt[4].loadFromFile(sciezka4);
    //sprite.setTexture(txt[type]);
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
void bron::Update(float posX,float posY,float degree,bool *EnterP,short type)
{
    sprite.setTexture(&txt[type]);
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
    void graj_dzwiek();
    float dist();
public:
    void Update(AI_Eq *Eq,unsigned int *targetHP,short w_rece);
    bool dotykaPostaci(int i);
    AI(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka_bron,std::string sciezka2,std::string sciezka3,float x,float y,float stosX,float stosY);
};
AI::AI(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka_bron,std::string sciezka2,std::string sciezka3,float x,float y,float stosX,float stosY)
    :Postac(window1,sciezka,sciezka1,sciezka2,sciezka3,"","",x,y,stosX,stosY)
{
    mieso.loadFromFile("Textures//porkchop_raw.png");
    b1.loadFromFile(sciezka_bron);
    B1.setTexture(b1);
    B1.setScale(0.08,0.08);
}
void AI::graj_dzwiek()
{
    if(sound.getStatus() == sf::Sound::Playing)
    {
        return;
    }
    unsigned short i=(std::rand()%3)+1;
    if(i==1)
    {
        sound.setBuffer(buffer1);
    }else if(i==2)
    {
        sound.setBuffer(buffer2);
    }
    sound.play();
}
void AI::ustawBron()
{
    if(postac.getScale().x>0)
    {
        B1.setPosition(posX+80*stosX,670*stosY);
        B1.setScale(0.08*stosX,0.08*stosY);
    }
    else
    {
        B1.setPosition(posX-80*stosX,670*stosY);
        B1.setScale(-0.08*stosX,0.08*stosY);
    }

}
bool AI::dotykaPostaci(int i)
{
        float bX=bullet_wsk[i]->posX;
        float bY=bullet_wsk[i]->posY;
        //float originX=postac.getOrigin().x;
        //float originY=postac.getOrigin().y;
        float x=postac.getPosition().x;
        float y=postac.getPosition().y;
       //y-=originY;
       //x-=originX;
        bY+=100;
        float sizeX=txt.getSize().x;
        float sizeY=txt.getSize().y;
        sizeX*=postac.getScale().x;
        sizeY*=postac.getScale().y;
        if(bX>(x) && bX<(x+sizeX))
        {
            if(bY>(y) && bY<(y+sizeY))
            {
                if(bullet_wsk[i]->fly==true)
                {
                    bullet_wsk[i]->fly=false;
                    return true;
                }else return false;
            }else return false;
        }else return false;
}
float AI::dist()
{
    return abs(posX-window.getSize().x/2);
}
void AI::Update(AI_Eq *Eq,unsigned int *targetHP,short w_rece)
{
    int przedzial;
    int losowa=std::rand()%2000;
    if(losowa==1)
    {
        move_to_side(Right);
        do
        {
            przedzial=1;
            postac.move(0.8*czas_na_klatke(),0);
            przedzial++;
        }while(std::rand()%przedzial==1 && przedzial<=200*czas_na_klatke());
    }
    if(losowa==0)
    {
        move_to_side(Left);
        do
        {
            przedzial=1;
            postac.move(-0.8*czas_na_klatke(),0);
            przedzial++;
        }while(std::rand()%przedzial==1 && przedzial<=200*czas_na_klatke());
    }
    if(losowa==3 && dist()<300 /*&& std::rand()%3==1*/)
    {
        if(*targetHP>0)
        {
            *targetHP-=10;
            graj_dzwiek();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        postac.move(-0.8*czas_na_klatke(),0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        postac.move(0.8*czas_na_klatke(),0);
    }
    posX=postac.getPosition().x;
    posY=postac.getPosition().y;
    for(int i=0;i<10;i++)
    {
        if(dotykaPostaci(i)==true)
        {
            switch(w_rece)
            {
            case 0 || 1:
                {
                    if(Eq->HP>=10)
                    {
                    Eq->HP-=10;
                    }
                }
                break;
            case 2:
                {
                    if(Eq->HP>=20)
                    {
                    Eq->HP-=20;
                    }
                }
                break;
            case 3:
                {
                    if(Eq->HP>=40)
                    {
                    Eq->HP-=40;
                    }
                }
                break;
            case 4:
                {
                    if(Eq->HP>=10)
                    {
                    Eq->HP-=10;
                    }
                }
                break;
            case 5:
                {
                    /*if(Eq->HP>=10)
                    {
                    Eq->HP-=10;
                    }*/
                }
                break;
            }

        }
    }
    if(postac.getScale().x>0)
    {
        white.setPosition(stosX*posX-50,stosY*posY-100);
        for(int i=0;i<10;i++)
        {
            red[i].setPosition(stosX*posX-50+20*i,stosY*posY-100);
        }
    }
    else
    {
        white.setPosition(stosX*posX-150,stosY*posY-100);
        for(int i=0;i<10;i++)
        {
            red[i].setPosition(stosX*posX-150+20*i,stosY*posY-100);
        }
    }
    ustawBron();
    if(false)
        hand_degree+=0.2;
    if(false)
        hand_degree-=0.2;
    if(Eq->HP<=10)
    {
        postac.setTexture(mieso);
    }
    window.draw(postac);
    if(Eq->HP>10)
        window.draw(B1);

    window.draw(white);
    for(int i=0;static_cast<unsigned int>(i)<Eq->HP/10;i++)
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
void skrzynka_fall(int GroundLevel,float x,float y,Equipment *Eq)
{
    skrzynka.posX=skrzynka.rect.getPosition().x;
    skrzynka.posY=skrzynka.rect.getPosition().y;
    if(skrzynka.posY<GroundLevel)
    {
        skrzynka.vs+=0.0001*czas_na_klatke();
        skrzynka.rect.move(0,skrzynka.vs*czas_na_klatke());
    }
    if(skrzynka.posY>=GroundLevel)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            skrzynka.rect.move(-0.8*czas_na_klatke(),0);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            skrzynka.rect.move(0.8*czas_na_klatke(),0);
        }
        if(x<skrzynka.posX && y>GroundLevel-100)
        {
            if(skrzynka.posX-x<100)
                {
                    skrzynka_off(Eq);
                }
        }else if(x-skrzynka.posX<100)
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
bool mozna_strzelac(int w_rece,sf::Clock *przeladowanie)
{
    sf::Time time=przeladowanie->getElapsedTime();
    switch (w_rece)
    {
    case 0:
        return false;
        break;
    case 1:
        {
            if(time.asSeconds()>2)
            {
                przeladowanie->restart();
                return true;
            }else return false;
        }
    case 2:
        {
            if(time.asSeconds()>0.3)
            {
                przeladowanie->restart();
                return true;
            }else return false;
        }
        break;
    case 3:
        {
            if(time.asSeconds()>5)
            {
                przeladowanie->restart();
                return true;
            }else return false;
        }
        break;
    case 4:
        {
            if(time.asSeconds()>0.2)
            {
                przeladowanie->restart();
                return true;
            }else return false;
        }
        break;
    case 5:
        {
            if(time.asSeconds()>1)
            {
                przeladowanie->restart();
                return true;
            }else return false;
        }
        break;
    default: return false;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void Config()
{
    int xSize,ySize;
    std::string sciezka="Config.txt";
    std::string line="";
    std::fstream config_file;
    config_file.open(sciezka,std::ios::in);
    if(config_file.good()==true)
    {
        for(int i=0;i<2;i++)
        {
            getline(config_file,line);
            switch(i)
            {
            case 0:
                {
                    unsigned int numberOfX=line.find("x");
                    if(numberOfX!=std::string::npos)
                    {
                        std::string s1,s2;
                        s1=s2=line;
                        s1.erase(0,numberOfX+1);
                        s2.erase(numberOfX,line.size());
                        //std::cout<<s1<<"\t"<<s2<<std::endl;
                        ySize=std::stoi(s2);
                        xSize=std::stoi(s1);
                    }
                    else
                    {
                        ySize=1080;
                        xSize=1920;
                    }

                    break;
                }
            case 1:
                {
                    if(line=="none")
                    {
                        frameLimit=0;
                    }else
                        frameLimit=std::stoi(line);
                    break;
                }
            case 2:
                {
                    setting.antialiasingLevel=std::stoi(line);
                    break;
                }
            default: break;
            }
        }

    }
    config_file.close();
    Xokna=xSize;
    Yokna=ySize;
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    setting.antialiasingLevel=0;
    interior=outside;
    bool Menu_misje=false;
    sf::Clock liczZrzut;
    sf::Clock przeladowanie;
    srand(time(NULL));
    Config();
    sf::RenderWindow window(sf::VideoMode(Yokna,Xokna,64), "Dziadek Swinka",sf::Style::Default,setting);
    const float stosX=1080.f/Xokna;   std::cout<<stosX<<std::endl;
    const float stosY=1920.f/Yokna;   std::cout<<stosY<<std::endl;
    const float GroundLevel=700.f/stosY;
    Postac Dziadek(window,"Textures//dziadek.png","Textures//dziadek_dmg.png","Sounds//dziadek1.wav","Sounds//dziadek2.wav","","Sounds//dziadek4.wav",window.getSize().x/2,GroundLevel,stosX,stosY);
    AI peppa(window,"Textures//obrazek.png","Textures//obrazek_dmg.png","Textures//noz.png","Sounds//peppa1.wav","Sounds//smiech1.wav",100,GroundLevel-50,stosX,stosY);
    AI mama(window,"Textures//mama_swinka.png","","Textures//pistolet.png","","",1300,GroundLevel-50,stosX,stosY);                                                                                      //dorobic brakujace pliki
    Background background(window,"Textures//grass.png",100,"Textures//grandpahouse.png",-800,"Textures//house.png",900,"Textures//shop.png",stosX,stosY);
    button Misje_bt(window,"Textures//bm.png","Textures//bmc.png",1600.f/stosX,20.f/stosY,stosX,stosY);
    button Misja1_bt(window,"Textures//m1.png","Textures//m1c.png",1520.f/stosX,80.f/stosY,stosX,stosY);
    button Misja2_bt(window,"Textures//m2.png","Textures//m2c.png",1670.f/stosX,80.f/stosY,stosX,stosY);
    button Sklep_bt(window,"Textures//sklep.png","Textures//sklepc.png",550.f/stosX,5.f/stosY,stosX,stosY);
    Sklep_bt.scaleX=0.45/stosX;
    Sklep_bt.scaleY=0.45/stosY;
    Equipment Eq(window,stosX,stosY);
    bron karabin(window,"Textures//ak47.png","Textures//pistolet.png","Textures//bazooka.png","Textures//uzi.png");
    skrzynki();
    sf::Sprite GameOver;
    sf::Texture gameover;
    gameover.loadFromFile("Textures//end.jpg");
    GameOver.setTexture(gameover);
    system("cls");
    if(frameLimit!=0)
        window.setFramerateLimit(frameLimit);

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
                    if(mozna_strzelac(Eq.w_rece,&przeladowanie)==true)
                    {
                        EnterPressed=true;
                        Eq.ammunition--;
                    }

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
                level=0;
            }
            else
                if(!Menu_misje)
                    Menu_misje=1;
        }
        if(Misja1_bt.isPressed())
        {
            if(level==0 || true)
            {
                level=1;
                level_setUp(1,&Eq,&peppaEq,&mamaEq);
            }
        }
        if(Misja2_bt.isPressed())
        {
            if(level==1 || true)
            {
                level=2;
                level_setUp(2,&Eq,&peppaEq,&mamaEq);
            }
        }
        if(Sklep_bt.isPressed())
        {
            if(panelSklep)
            {
                panelSklep=0;
            }else panelSklep=1;
        }
        window.clear(sf::Color(138,191,255));
        if(Eq.HP>0)
        {
            if(!panelSklep)
            {
                background.Update(&interior,level,&panelSklep);
                if(interior==outside)
                {
                    if(skrzynka.active)
                    {
                        skrzynka_fall(GroundLevel,Dziadek.posX,Dziadek.posY,&Eq);
                        window.draw(skrzynka.rect);
                    }

                    Dziadek.Update(Eq.HP,przeladowanie.getElapsedTime(),Eq.w_rece);
                    karabin.Update(Dziadek.posX,Dziadek.posY,Dziadek.getDegree(),&EnterPressed,Eq.w_rece);
                    if(level==1)
                    {
                        if(peppaEq.HP>0)
                            peppa.Update(&peppaEq,&Eq.HP,Eq.w_rece);
                        if(peppaEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(50);
                        }
                    }
                    if(level==2)
                    {
                        if(mamaEq.HP>0)
                            mama.Update(&mamaEq,&Eq.HP,Eq.w_rece);
                        if(mamaEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(70);
                        }
                    }
                }
                Misje_bt.Update(ButtonPressed);
                if(Menu_misje)
                {
                    Misja1_bt.Update(ButtonPressed);
                }
                if(Menu_misje)
                {
                    Misja2_bt.Update(ButtonPressed);
                }
            }
            Eq.Update(panelSklep,ButtonPressed);
            Sklep_bt.Update(ButtonPressed);
            if(interior==pociong)
                    Eq.pociag();
        }else
        {
            window.draw(GameOver);
        }

        window.display();
        poprz_klatka=klatka.getElapsedTime();
        klatka.restart();
    }
    EnterPressed=false;

    return 0;
}
