#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <cmath>
#include <fstream>

#include "Network.hpp"
#include "side.hpp"
#include "Equipment.hpp"
#include "level.hpp"
#include "button.hpp"
#include "Background.hpp"
#include "mode.hpp"
#include "Saves.hpp"
#include "IniConfig.hpp"
#include "Loading.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

//using std::cout;
//using std::endl;

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
AI_Eq peppaEq,mamaEq,tataEq,georgeEq;
obj skrzynka;
sf::Clock klatka;
sf::Time poprz_klatka;

sf::ContextSettings setting;

class AI;
class Postac;
class bullet;
class Network;

bullet* bullet_wsk[10]={nullptr};

unsigned int Xokna=1920,Yokna=1080;
float frameLimit=0;

float Vol[10]={60,20,50,5,40,0,0,0,0,0};              // 0-main volume,1-muzyka w tle, 2-dzidek dzialogi, 3-bron,4-inne dialogi


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
    bullet(sf::RenderWindow &window1,std::string sciezka,int i,AI_Eq *newEq);
    void setPosition(float posX, float posY);
    void setRotation(float dir);
    void setRotationAI(float dir);
    float posX,posY;
    float dir;
    float AI_fix={0.f};
    bool fly;
    bool k={0.f};
};
bullet::bullet(sf::RenderWindow &window1,std::string sciezka,int i):window(window1)
{
    txt.loadFromFile(sciezka);
    sprite.setTexture(txt);
    sprite.setScale(0.05,0.05);
    fly=false;
    bullet_wsk[i]=this;
}
bullet::bullet(sf::RenderWindow &window1,std::string sciezka,int i,AI_Eq *newEq):window(window1)
{
    txt.loadFromFile(sciezka);
    sprite.setTexture(txt);
    sprite.setScale(0.05,0.05);
    fly=false;
    newEq->bullet_wsk[i]=this;
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
void bullet::setRotationAI(float dir)
{
    if(dir>-85)
    {
        sprite.setRotation(-dir+90);
        sprite.setScale(0.05,0.05);
    }
    else
    {
         sprite.setRotation(dir-90);
         sprite.setScale(-0.05,-0.05);
    }
}

void bullet::Update()
{
    posX=sprite.getPosition().x;
    posY=sprite.getPosition().y;
    double alfa;
    double a,b,c=1.2;

    alfa=sprite.getRotation()+90;
    alfa*=M_PI/180.f;

    if(k)
    {
        AI_fix*=M_PI/180.f;
        alfa+=AI_fix;
        a=c*(sin(alfa));
        b=c*(cos(alfa));
        sprite.move(b*czas_na_klatke(),a*czas_na_klatke());
    }
    if(!k)
    {

        a=c*(sin(alfa));
        b=c*(cos(alfa));
        sprite.move(-b*czas_na_klatke(),-a*czas_na_klatke());
    }


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
class Postac
{
private:
    friend class Network;
    void graj_dzwiek();
    void graj_dzwiek(unsigned short i);
    float oblicz_czas(int w_rece,float czas);
    bool jumpAllowed;
    sf::Font OswaldRegular;
    sf::Text czas;
    bool dotykaPostaci(int i,AI_Eq *myEq);
    AI_Eq *t1;
    AI_Eq *t2;
    AI_Eq *t3;
protected:
    sf::SoundBuffer buffer1,buffer2,buffer3,buffer4;
    sf::Sound sound;
    sf::RenderWindow &window;
    sf::Texture txt,txt2,red_txt,yellow_txt,white_txt;
    sf::Sprite postac,red[10],yellow[10],white,white2;
    sf::Clock od_obrazenia;
    sf::Time czas_od_dmg;
    void Fall();
    void move_to_side(side Side);
    float vs=0;
    float stosX,stosY;
public:
    float hand_degree=0;
    operator=(Postac &obj);
    void clockRestart();
    //Postac();
    Postac(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka2,std::string sciezka3,std::string sciezka4,std::string sciezka5,float x,float y,float stosX,float stosY);
    Postac(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka2,std::string sciezka3,std::string sciezka4,std::string sciezka5,float x,float y,float stosX,float stosY,AI_Eq *t1,AI_Eq *t2,AI_Eq *t3);
    float getDegree();
    side Wside();
    float posX,posY;
    unsigned int Update(unsigned int Hp,int boostHp,sf::Time czas_p,int w_rece);
};
Postac::Postac(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka2,std::string sciezka3,std::string sciezka4,std::string sciezka5,float x,float y,float stosX,float stosY)
    :window(window1),stosX(stosX),stosY(stosY)
{
    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    red_txt.loadFromFile("Textures//GUI//red_.png");
    yellow_txt.loadFromFile("Textures//GUI//yellow_.png");
    white_txt.loadFromFile("Textures//GUI//white_.png");
    czas.setFont(OswaldRegular);

    for(int i=0;i<10;i++)
    {
        red[i].setTexture(red_txt);
        red[i].setScale(0.25,0.25);
        yellow[i].setTexture(yellow_txt);
        yellow[i].setScale(0.25,0.25);
    }

    buffer1.loadFromFile(sciezka2);
    buffer2.loadFromFile(sciezka3);
    buffer3.loadFromFile(sciezka4);
    buffer4.loadFromFile(sciezka5);
    white.setTexture(white_txt);
    white2.setTexture(white_txt);
    txt.loadFromFile(sciezka);
    txt2.loadFromFile(sciezka1);
    postac.setTexture(txt);
    postac.setScale(0.5/stosX,0.5/stosY);
    postac.setOrigin((txt.getSize().x)*postac.getScale().x/(stosX*2),(txt.getSize().y)*postac.getScale().y/(stosY*2));
    postac.setPosition(x/stosX,y/stosY);
    posX=x;
    posY=y;
}
Postac::Postac(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka2,std::string sciezka3,std::string sciezka4,std::string sciezka5,float x,float y,float stosX,float stosY,AI_Eq *t1,AI_Eq *t2,AI_Eq *t3)
    :window(window1),stosX(stosX),stosY(stosY),t1(t1),t2(t2),t3(t3)
{
    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    red_txt.loadFromFile("Textures//GUI//red_.png");
    yellow_txt.loadFromFile("Textures//GUI//yellow_.png");
    white_txt.loadFromFile("Textures//GUI//white_.png");
    czas.setFont(OswaldRegular);

    for(int i=0;i<10;i++)
    {
        red[i].setTexture(red_txt);
        red[i].setScale(0.25,0.25);
        yellow[i].setTexture(yellow_txt);
        yellow[i].setScale(0.25,0.25);
    }

    buffer1.loadFromFile(sciezka2);
    buffer2.loadFromFile(sciezka3);
    buffer3.loadFromFile(sciezka4);
    buffer4.loadFromFile(sciezka5);
    white.setTexture(white_txt);
    white2.setTexture(white_txt);
    txt.loadFromFile(sciezka);
    txt2.loadFromFile(sciezka1);
    postac.setTexture(txt);
    postac.setScale(0.5/stosX,0.5/stosY);
    postac.setOrigin((txt.getSize().x)*postac.getScale().x/(stosX*2),(txt.getSize().y)*postac.getScale().y/(stosY*2));
    postac.setPosition(x/stosX,y/stosY);
    posX=x;
    posY=y;
}
Postac::operator=(Postac &obj)
{
    obj.posY=posY;
    obj.posX=posX;
    obj.hand_degree=hand_degree;
}
side Postac::Wside()
{
    if(postac.getScale().x>0)
        return Right;
    else return Left;
}
void Postac::clockRestart()
{
    od_obrazenia.restart();
}
bool Postac::dotykaPostaci(int i,AI_Eq *myEq)
{
        float bX=myEq->bullet_wsk[i]->posX;
        float bY=myEq->bullet_wsk[i]->posY;
        //float originX=postac.getOrigin().x;
        //float originY=postac.getOrigin().y;
        float x=postac.getPosition().x;
        float y=postac.getPosition().y;
       //y-=originY;
       //x-=originX;
        bY+=100;
        float sizeX=txt.getSize().x;
        float sizeY=txt.getSize().y;
        bool isRight;
        if(postac.getScale().x>0)
            isRight=false;
        else isRight=true;

        x-=txt.getSize().x*isRight;

        sizeX*=abs(postac.getScale().x);
        sizeY*=abs(postac.getScale().y);

        if(bX>(x) && bX<(x+sizeX))
        {
            if(bY>(y) && bY<(y+sizeY))
            {
                if(myEq->bullet_wsk[i]->fly==true)
                {
                    myEq->bullet_wsk[i]->fly=false;
                    return true;
                }else return false;
            }else return false;
        }else return false;
}//*/
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
    sound.setVolume(Vol[2]*Vol[0]/100);
    sound.play();
}
void Postac::graj_dzwiek()
{
    srand(time(NULL));
    unsigned short i=(std::rand()%5);
    graj_dzwiek(i);
}
unsigned int Postac::Update(unsigned int Hp,int boostHp,sf::Time czas_p,int w_rece)
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
        white2.setPosition(posX-50,posY-122);
        for(int i=0;i<10;i++)
        {
            red[i].setPosition(posX-50+20*i,posY-100);
            yellow[i].setPosition(posX-50+20*i,posY-122);
        }
    }
    else
    {
        czas.setPosition(posX-110,posY-220);
        white.setPosition(posX-150,posY-100);
        white2.setPosition(posX-150,posY-122);
        for(int i=0;i<10;i++)
        {
            red[i].setPosition(posX-150+20*i,posY-100);
            yellow[i].setPosition(posX-150+20*i,posY-122);
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

    unsigned int hp_=0;
    for(int i=0;i<10;i++)
    {
        if(dotykaPostaci(i,t1)==true)
            hp_+=10;
        if(dotykaPostaci(i,t2)==true)
            hp_+=10;
        if(dotykaPostaci(i,t3)==true)
            hp_+=20;
    }
    if(hp_>0)
        od_obrazenia.restart();

    czas_od_dmg=od_obrazenia.getElapsedTime();
    if(czas_od_dmg.asSeconds()<0.4)
    {
        postac.setTexture(txt2);
    }else postac.setTexture(txt);

    window.draw(postac);
    window.draw(white);
    if(boostHp!=0)
        window.draw(white2);
    window.draw(czas);
    Hp/=10;
    boostHp/=10;
    for(int i=0;static_cast<unsigned int>(i)<Hp;i++)
        window.draw(red[i]);
    for(int i=0;i<boostHp;i++)
        window.draw(yellow[i]);

    return hp_;
}
float Postac::getDegree()
{
    return hand_degree;
}
void Postac::Fall()
{
    float gravity=0.0001;
    if(postac.getPosition().y>=548)
    {
        jumpAllowed=true;
    }
    if(postac.getPosition().y + (txt.getSize().y) / 4 <= window.getSize().y - 380/stosY && postac.getPosition().y >= 0+5)
    {
        if(true==sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jumpAllowed==true)
        {
            vs=-0.1;
            postac.move(0,vs*czas_na_klatke()*3);
            if(postac.getPosition().y<=500)
                jumpAllowed=false;
        }
        else //if(false==sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
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

class bron
{
private:
    sf::Texture txt[5];
protected:
    sf::RenderWindow &window;
    sf::RectangleShape sprite;
    sf::SoundBuffer buffer;
    void wystrzel(float degreee);
    void ustawPocisk(short i,float degre);
public:
    sf::Sound piu_piu;
    void move_to_side(side Side);
    bullet Bullet[10] = {   bullet(window,"Textures//Items//bullet.png",0),
                            bullet(window,"Textures//Items//bullet.png",1),
                            bullet(window,"Textures//Items//bullet.png",2),
                            bullet(window,"Textures//Items//bullet.png",3),
                            bullet(window,"Textures//Items//bullet.png",4),
                            bullet(window,"Textures//Items//bullet.png",5),
                            bullet(window,"Textures//Items//bullet.png",6),
                            bullet(window,"Textures//Items//bullet.png",7),
                            bullet(window,"Textures//Items//bullet.png",8),
                            bullet(window,"Textures//Items//bullet.png",9)};
    bron(sf::RenderWindow &window1,std::string sciezka,std::string sciezka2,std::string sciezka3,std::string sciezka4);
    void Update(float posX,float posY,float degree,bool *EnterP,short type);
};
bron::bron(sf::RenderWindow &window1,std::string sciezka,std::string sciezka2,std::string sciezka3,std::string sciezka4):window(window1)
{
    buffer.loadFromFile("Sounds//piu_piu.wav");
    piu_piu.setBuffer(buffer);
    piu_piu.setVolume(Vol[3]*Vol[0]/100);
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
            piu_piu.play();
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
    Bullet[i].setPosition(sprite.getPosition().x,sprite.getPosition().y-20);
    if(sprite.getScale().x>0)
        Bullet[i].k=true;
    else
        Bullet[i].k=false;
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

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
/*
class AI_Bron
    :public bron
{
private:
    sf::Texture txt;
    void wystrzel(float degreee);
    void ustawPocisk(short i,float degre);
public:
    bullet Bullet[10] = {   bullet(window,"Textures//Items//bullet.png",0),
                            bullet(window,"Textures//Items//bullet.png",1),
                            bullet(window,"Textures//Items//bullet.png",2),
                            bullet(window,"Textures//Items//bullet.png",3),
                            bullet(window,"Textures//Items//bullet.png",4),
                            bullet(window,"Textures//Items//bullet.png",5),
                            bullet(window,"Textures//Items//bullet.png",6),
                            bullet(window,"Textures//Items//bullet.png",7),
                            bullet(window,"Textures//Items//bullet.png",8),
                            bullet(window,"Textures//Items//bullet.png",9)};

    void Update(float posX,float posY,float degree,bool *EnterP);
    AI_Bron(sf::RenderWindow &window1,std::string sciezka);
};
AI_Bron::AI_Bron(sf::RenderWindow &window1,std::string sciezka)
    :bron(window,sciezka,"","","")
{
    sprite.setSize(sf::Vector2f(1024,370));
    txt.loadFromFile(sciezka);
    sprite.setTexture(&txt);
    sprite.setScale(-0.3,0.3);
    sprite.setOrigin(700,250);
    sprite.setRotation(0);
}
void AI_Bron::wystrzel(float degree)
{
    short i=0;
    while(i<10)
    {
        if(Bullet[i].fly==false)
        {
            piu_piu.play();
            Bullet[i].fly=true;
            ustawPocisk(i,degree);
            break;
        }
        else
            i++;
    }
}
void AI_Bron::ustawPocisk(short i,float degree)
{
    Bullet[i].setPosition(sprite.getPosition().x,sprite.getPosition().y);
    Bullet[i].setRotation(degree);
    if(sprite.getScale().x>0)
        Bullet[i].k=true;
    else
        Bullet[i].k=false;
}
void AI_Bron::Update(float posX,float posY,float degree,bool *EnterP)
{
    sprite.setTexture(&txt);
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
*/


//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

class AI
    :public Postac
{
private:
    friend class Network;
    sf::SoundBuffer buffer;
    sf::Sound piu;
    sf::Clock przeladowanie;
    sf::Time time;
    sf::Texture b1;
    sf::Texture mieso;
    sf::Sprite B1;
    AI_Eq &mEq;
    void ustawBron();
    void graj_dzwiek();
    void wystrzel();
    void ustawPocisk(short i,float degree);
    float dist();
    double liczKat(Postac &target);
    double scaleX,scaleY;
    double corX,corY;
    float x=0;
    int type;
    float przeladowanie_time[4]={2,1,5,0.5};
    bool dmg_from_peppa=false;
public:
    void Update1(AI_Eq *Eq,int *targetHP,int *boostHp,short w_rece,Postac *T);
    void Update2(AI_Eq *Eq,int *targetHP,int *boostHp,short w_rece,Postac *Target);
    bool dotykaPostaci(int i);
    AI(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka_bron,const int type,std::string sciezka2,std::string sciezka3,float x,float y,float stosX,float stosY,AI_Eq *mEg);
    bullet Bullet_AI[10] = {bullet(window,"Textures//Items//bullet.png",0,&mEq),
                            bullet(window,"Textures//Items//bullet.png",1,&mEq),
                            bullet(window,"Textures//Items//bullet.png",2,&mEq),
                            bullet(window,"Textures//Items//bullet.png",3,&mEq),
                            bullet(window,"Textures//Items//bullet.png",4,&mEq),
                            bullet(window,"Textures//Items//bullet.png",5,&mEq),
                            bullet(window,"Textures//Items//bullet.png",6,&mEq),
                            bullet(window,"Textures//Items//bullet.png",7,&mEq),
                            bullet(window,"Textures//Items//bullet.png",8,&mEq),
                            bullet(window,"Textures//Items//bullet.png",9,&mEq)};
};
AI::AI(sf::RenderWindow &window1,std::string sciezka,std::string sciezka1,std::string sciezka_bron,const int type,std::string sciezka2,std::string sciezka3,float x,float y,float stosX,float stosY,AI_Eq *mEq)
    :Postac(window1,sciezka,sciezka1,sciezka2,sciezka3,"","",x,y,stosX,stosY),type(type),mEq(*mEq)
{
    buffer.loadFromFile("Sounds//piu_piu.wav");
    mieso.loadFromFile("Textures//Charakters//porkchop_raw.png");
    b1.loadFromFile(sciezka_bron);
    B1.setTexture(b1);
    piu.setBuffer(buffer);
    piu.setVolume(Vol[0]*Vol[3]/100);
    hand_degree=0;
    switch(type)
    {
    case 0:
        {
            corX=60;
            corY=680;
            scaleX=-0.08;
            scaleY=0.08;
            break;
        }
    default:
        {
            scaleY=scaleX=0.3;
            corX=140;
            corY=730;
            B1.setOrigin(700,250);
            break;
        }
    }
    B1.setScale(scaleX,scaleY);
}
void AI::graj_dzwiek()
{
    if(sound.getStatus() == sf::Sound::Playing)
    {
        return;
    }
    unsigned short i=(std::rand()%6)+1;
    if(i==1)
    {
        sound.setBuffer(buffer1);
    }else if(i==2)
    {
        sound.setBuffer(buffer2);
    }else return;
    sound.setVolume(Vol[4]*Vol[0]/100);
    sound.play();
}
void AI::ustawBron()
{
    if(postac.getScale().x>0)
    {
        B1.setPosition(posX+corX*stosX,corY*stosY);
        B1.setScale(-scaleX*stosX,scaleY*stosY);
        B1.setRotation(hand_degree);

    }
    else
    {
        B1.setPosition(posX-corX*stosX,corY*stosY);
        B1.setScale(scaleX*stosX,scaleY*stosY);
        if(type!=0)
            B1.setRotation(hand_degree+180);
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
        bool isRight;
        if(postac.getScale().x>0)
            isRight=false;
        else isRight=true;

        x-=txt.getSize().x*isRight;

        sizeX*=abs(postac.getScale().x);
        sizeY*=abs(postac.getScale().y);
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

void AI::ustawPocisk(short i,float degree)
{
    Bullet_AI[i].setPosition(B1.getPosition().x,B1.getPosition().y-20);
    Bullet_AI[i].setRotationAI(degree);
    if(B1.getScale().x<0)
    {
        Bullet_AI[i].k=true;
    }
    else if(B1.getScale().x>0)
    {
        Bullet_AI[i].k=false;
    }
}
void AI::wystrzel()
{
    float degree=-hand_degree;
    short i=0;
    while(i<10)
    {
        if(Bullet_AI[i].fly==false && time.asSeconds()>przeladowanie_time[type-1])
        {
            ustawPocisk(i,degree);
            piu.play();
            Bullet_AI[i].fly=true;
            przeladowanie.restart();
            break;

        }
        else
            i++;
    }
}
void AI::Update2(AI_Eq *Eq,int *targetHP,int *boostHp,short w_rece,Postac *Target)
{
    time=przeladowanie.getElapsedTime();
    Postac &target=*Target;
    hand_degree=liczKat(target);
    if(Eq->HP>10)
        wystrzel();
    graj_dzwiek();
    Update1(Eq,targetHP,boostHp,w_rece,Target);
    for(short i=0;i<10;i++)
    {
        Bullet_AI[i].AI_fix=180.f;
        if(Bullet_AI[i].fly==true)
        {
            Bullet_AI[i].Update();
        }
    }
}
void AI::Update1(AI_Eq *Eq,int *targetHP,int *boostHp,short w_rece,Postac *T)
{
    if(type>0)
    {
        if(hand_degree>(-84))
        {
            move_to_side(Right);
        }else if(hand_degree<(-84))
        {
            move_to_side(Left);
        }
    }

    int przedzial;
    int losowa=std::rand()%2000;
    if(losowa==1 && type==0)
    {

        move_to_side(Right);
        do
        {
            przedzial=1;
            postac.move(0.8*czas_na_klatke(),0);
            przedzial++;
        }while(std::rand()%przedzial==1 && przedzial<=200*czas_na_klatke());
    }
    if(losowa==0 && type==0)
    {
        move_to_side(Left);
        do
        {
            przedzial=1;
            postac.move(-0.8*czas_na_klatke(),0);
            przedzial++;
        }while(std::rand()%przedzial==1 && przedzial<=200*czas_na_klatke());
    }
    if(losowa==3 && dist()<300 /*&& std::rand()%3==1*/ && type==0)
    {
        int minusHP=10;
        if(*boostHp!=0)
        {
            if(minusHP<=*boostHp)
                *boostHp-=minusHP;
            else
            {
                *boostHp=0;
                minusHP-=*boostHp;
                if(minusHP<=*targetHP)
                    *targetHP-=minusHP;
            }
        }else
            if(minusHP<=*targetHP)
                *targetHP-=minusHP;
            else *targetHP=0;
        T->clockRestart();
        graj_dzwiek();
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
            od_obrazenia.restart();
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

    czas_od_dmg=od_obrazenia.getElapsedTime();
    if(czas_od_dmg.asSeconds()<0.3)
    {
        postac.setTexture(txt2);
    }else postac.setTexture(txt);
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
double AI::liczKat(Postac &target)
{
    double x,y;
    double x1,y1;
    double x2,y2;
    x1=this->postac.getPosition().x;
    y1=this->postac.getPosition().y;
    x2=target.posX;
    y2=target.posY;
    x=x2-x1;
    y=y1-y2;
    return atan2(x,y)*180/M_PI-90;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void losuj_zrzut()
{
    unsigned short l=(std::rand()%10)+1;
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
    skrzynka.txt1.loadFromFile("Textures//Items//apteczka.png");
    skrzynka.txt2.loadFromFile("Textures//Items//ammo.png");
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
void setMulti(Network *net,Postac *postac,AI *ai,AI_Eq *aiEq,unsigned int HP,float x,bron *Bron)
{

    float PosX[10],PosY[10],Dir[10];
    bool isFly[10];
    side Side;
    for(int i=0;i<10;i++)
    {
        PosX[i]=Bron->Bullet[i].posX;
        PosY[i]=Bron->Bullet[i].posY;
        Dir[i]=Bron->Bullet[i].dir;
        isFly[i]=Bron->Bullet[i].fly;
    }
    net->Update(x,
                postac->posY,
                postac->hand_degree,
                HP,
                Dir,
                PosX,
                PosY,
                isFly,
                postac->Wside());   //*/
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void usunBiale(std::string *line)
{
    std::string nowyString="";
    for(int i=0;i<256;i++)
    {
        if(line[i]!=" ")
        {
            nowyString+=line[i];
        }else
        if(line[i+1]==" ")
            break;
    }
    *line=nowyString;
}
void lineToSetup(std::string line,int i)
{
    usunBiale(&line);
    int xSize=1920,
        ySize=1080;
    switch(i)
    {
    case 0:
        {
            std::cout<<line;
            unsigned int numberOfX=line.find("x");
            if(numberOfX!=std::string::npos)
            {
                std::string s1,s2;
                s1=s2=line;
                s1.erase(0,numberOfX+1);
                s2.erase(numberOfX,line.size());
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
        default:
        {
            if(i<=12 && i>2)
            {
                if(line!="" && line!="\n")
                    {
                        Vol[i-2]=std::stof(line);
                    }
            }
            break;
        }
    }
    Xokna=xSize;
    Yokna=ySize;
}
void Config()
{
    try
    {
        int xSize=0,ySize=0;
        std::string sciezka="Config.txt";
        std::string line="";
        std::fstream config_file;
        config_file.open(sciezka,std::ios::in);
        if(config_file.good()==true)
        {
            for(int i=0;i<12||config_file.eof()==true;i++)
            {
                getline(config_file,line);
                lineToSetup(line,i);

            }
        }
        config_file.close();
    }
    catch(...)
    {
        Xokna=1920;
        Yokna=1080;
        frameLimit=0;
    }
    return;
}

std::string set_sezon()
{
    std::string sezon="";
    time_t t = time(nullptr);
    struct tm Tm = *localtime(&t);
    if(Tm.tm_mon==9 || Tm.tm_mon==11 || Tm.tm_mon==10 || Tm.tm_mon==0)
    {
        sezon="_winter";
    }else sezon="";
    return sezon;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
void application();
int main(int argc, char *argv[])
{
    while(true)
    {
        application();
    }
}

void application()
{
    setting.antialiasingLevel=0;
    interior=outside;
    //bool multiplayer=true;
    bool Menu_misje=false;
    sf::Clock liczZrzut;
    sf::Clock przeladowanie;
    srand(time(NULL));
    std::string *sezon=new std::string;
    *sezon=set_sezon();
    //Config();
    //config();
    sf::RenderWindow window(sf::VideoMode(Xokna,Yokna,64), "Dziadek Swinka",sf::Style::Default,setting);
    {
        auto image = sf::Image{};
        image.loadFromFile("Textures//Charakters//dziadek.png");
        window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    }
    LoadingScreen *Loading=new LoadingScreen(window);
    const float stosX=1920.f/Xokna;   //std::cout<<stosX<<std::endl;
    const float stosY=1080.f/Yokna;   //std::cout<<stosY<<std::endl;
    const float GroundLevel=700.f/stosY;
    Postac Dziadek(window,"Textures//Charakters//dziadek"+*sezon+".png","Textures//Charakters//dziadek_dmg"+*sezon+".png","Sounds//dziadek1.wav","Sounds//dziadek2.wav","","Sounds//dziadek4.wav",window.getSize().x/2,GroundLevel,stosX,stosY,&peppaEq,&mamaEq,&tataEq);
    Loading->Push();
    AI peppa(window,"Textures//Charakters//obrazek.png","Textures//Charakters//obrazek_dmg.png","Textures//Items//noz.png",0,"Sounds//peppa1.wav","Sounds//smiech1.wav",100,GroundLevel-50,stosX,stosY,&peppaEq);
    AI george(window,"Textures//Charakters//George.png","Textures//Charakters//George_dmg.png","Textures//Items//uzi.png",4,"","",300,GroundLevel-50,stosX,stosY,&peppaEq);
    Loading->Push();
    AI mama(window,"Textures//Charakters//mama_swinka.png","Textures//Charakters//mama_swinka_dmg.png","Textures//Items//pistolet.png",1,"Sounds//mama1.wav","Sounds//mama2.wav",1400,GroundLevel-50,stosX,stosY,&mamaEq);                                                                                      //dorobic brakujace pliki
    AI tata(window,"Textures//Charakters//tata_swinka.png","Textures//Charakters//tata_swinka_dmg.png","Textures//Items//ak47.png",2,"Sounds//tata1.wav","Sounds//tata2.wav",900,GroundLevel-50,stosX,stosY,&tataEq);                                                                                      //dorobic brakujace pliki
    Loading->Push();
    //AI_Eq aiEq;
    //AI multiCharacter(window,"Textures//Charakters//dziadek.png","","",0,"","",100,GroundLevel-50,stosX,stosY,&aiEq);

    Background background(window,"Textures//Background//grass",100,"Textures//Background//grandpahouse",-800,"Textures//Background//house",900,"Textures//Background//shop",stosX,stosY,*sezon);
    delete sezon;
    Loading->Push();
    button Misje_bt(window,"Textures//GUI//bm.png","Textures//GUI//bmc.png",1600.f/stosX,20.f/stosY,stosX,stosY);
    button Misja1_bt(window,"Textures//GUI//m1.png","Textures//GUI//m1c.png",1520.f/stosX,80.f/stosY,stosX,stosY);
    button Misja2_bt(window,"Textures//GUI//m2.png","Textures//GUI//m2c.png",1670.f/stosX,80.f/stosY,stosX,stosY);
    button Misja3_bt(window,"Textures//GUI//m3.png","Textures//GUI//m3c.png",1520.f/stosX,140.f/stosY,stosX,stosY);
    button Misja4_bt(window,"Textures//GUI//m4.png","Textures//GUI//m4c.png",1670.f/stosX,140.f/stosY,stosX,stosY);
    button Misja5_bt(window,"Textures//GUI//m5.png","Textures//GUI//m5c.png",1520.f/stosX,200.f/stosY,stosX,stosY);
    button Misja6_bt(window,"Textures//GUI//m6.png","Textures//GUI//m6c.png",1670.f/stosX,200.f/stosY,stosX,stosY);
    button Misja7_bt(window,"Textures//GUI//m7.png","Textures//GUI//m7c.png",1520.f/stosX,260.f/stosY,stosX,stosY);
    button Misja8_bt(window,"Textures//GUI//m8.png","Textures//GUI//m8c.png",1670.f/stosX,260.f/stosY,stosX,stosY);
    button Misja9_bt(window,"Textures//GUI//m9.png","Textures//GUI//m9c.png",1520.f/stosX,320.f/stosY,stosX,stosY);
    button Misja10_bt(window,"Textures//GUI//m10.png","Textures//GUI//m10c.png",1670.f/stosX,320.f/stosY,stosX,stosY);
    button Sklep_bt(window,"Textures//GUI//sklep.png","Textures//GUI//sklepc.png",550.f/stosX,5.f/stosY,stosX,stosY);

    button Restart(window,"Textures//GUI//restart.png","Textures//GUI//restartc.png",window.getSize().x/(2*stosX)-326,window.getSize().y/(2*stosY)-160,stosX,stosY);

    button saveBt(window,"Textures//GUI//zapisz.png","Textures//GUI//zapiszc.png",1100.f/stosX,5.f/stosY,stosX,stosY);
    button loadBt(window,"Textures//GUI//wczytaj.png","Textures//GUI//wczytajc.png",1250.f/stosX,5.f/stosY,stosX,stosY);
    Loading->Push();

    Sklep_bt.scaleX=0.45/stosX;
    Sklep_bt.scaleY=0.45/stosY;
    saveBt.scaleY=0.45/stosY;
    saveBt.scaleY=0.45/stosX;
    loadBt.scaleY=0.45/stosY;
    loadBt.scaleY=0.45/stosX;
    Loading->Push();
    Equipment Eq(window,stosX,stosY,Vol[0],Vol[1]);
    bron karabin(window,"Textures//Items//ak47.png","Textures//Items//pistolet.png","Textures//Items//bazooka.png","Textures//Items//uzi.png");
    Loading->Push();
    saveList List(window,stosX,stosY);
    skrzynki();
    sf::Sprite GameOver;
    sf::Texture gameover;
    gameover.loadFromFile("Textures//Background//end.jpg");
    GameOver.setTexture(gameover);
    bool odblokowane[10]={1,0,0,0,0,0,0,0,0,0};
    sf::Sprite lock[10];
    sf::Texture Lock;
    Lock.loadFromFile("Textures//GUI//lock.png");
    Loading->Push();
    for(short i=0;i<10;i++)
    {
        const float przesun_X=80/stosY;
        const float przesun_Y=10/stosY;
        lock[i].setTexture(Lock);
        lock[i].setScale(0.05,0.05);
        if(i%2==0)
            lock[i].setPosition(1575-przesun_X,(80+przesun_Y+(60*(i/2))));
        else
            lock[i].setPosition(1715+przesun_X,(80+przesun_Y+(60*(i/2))));
    }
    Loading->Push();
    //system("cls");
    /*Network *net;
    try
    {
        net=new Network;
    }
    catch(std::runtime_error e)
    {
        std::cout<<"Network class error\n"<<e.what()<<std::endl;
    }*/
    if(frameLimit!=0)
        window.setFramerateLimit(frameLimit);
    Loading->Push();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                exit(0);
            }
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
        }
        sf::Time time1=liczZrzut.getElapsedTime();
        if(time1.asSeconds()>4)
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
            if(odblokowane[0])
            {
                level=1;
                level_setUp(1,&Eq,&peppaEq,&mamaEq,&tataEq,&georgeEq);
            }
        }
        if(Misja2_bt.isPressed())
        {
            if(odblokowane[1])
            {
                level=2;
                level_setUp(2,&Eq,&peppaEq,&mamaEq,&tataEq,&georgeEq);
            }
        }
        if(Misja3_bt.isPressed())
        {
            if(odblokowane[2])
            {
                level=3;
                level_setUp(3,&Eq,&peppaEq,&mamaEq,&tataEq,&georgeEq);
            }
        }
        if(Misja4_bt.isPressed())
        {
            if(odblokowane[3])
            {
                level=4;
                level_setUp(4,&Eq,&peppaEq,&mamaEq,&tataEq,&georgeEq);
            }
        }
        if(Misja5_bt.isPressed())
        {
            if(odblokowane[4])
            {
                level=5;
                level_setUp(5,&Eq,&peppaEq,&mamaEq,&tataEq,&georgeEq);
            }
        }
        if(Misja6_bt.isPressed())
        {
            if(odblokowane[5])
            {
                level=6;
                level_setUp(6,&Eq,&peppaEq,&mamaEq,&tataEq,&georgeEq);
            }
        }if(Misja7_bt.isPressed())
        {
            if(odblokowane[6])
            {
                level=7;
                level_setUp(7,&Eq,&peppaEq,&mamaEq,&tataEq,&georgeEq);
            }
        }if(Misja8_bt.isPressed())
        {
            if(odblokowane[7])
            {
                level=8;
                level_setUp(8,&Eq,&peppaEq,&mamaEq,&tataEq,&georgeEq);
            }
        }if(Misja9_bt.isPressed())
        {
            if(odblokowane[8])
            {
                level=9;
                level_setUp(9,&Eq,&peppaEq,&mamaEq,&tataEq,&georgeEq);
            }
        }if(Misja10_bt.isPressed())
        {
            if(odblokowane[9])
            {
                level=10;
                level_setUp(10,&Eq,&peppaEq,&mamaEq,&tataEq,&georgeEq);
            }
        }
        if(saveBt.isPressed())
            List.save(&Eq);
        if(loadBt.isPressed())
            if(List.showList)
                List.showList=false;
            else List.showList=true;
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
            if(!panelSklep && List.showList==false)
            {
                Eq.pieniadze+=background.Update(&interior,level,&panelSklep,EnterPressed,czas_na_klatke());
                if(interior==outside)
                {
                    if(skrzynka.active)
                    {
                        skrzynka_fall(GroundLevel,Dziadek.posX,Dziadek.posY,&Eq);
                        window.draw(skrzynka.rect);
                    }
                    /*if(multiplayer==true && net->isConnect)
                    {
                        try
                        {
                        setMulti(net,&Dziadek,&multiCharacter,&aiEq,Eq.HP,background.x,&karabin);
                        }
                        catch(std::bad_alloc e)
                        {
                            std::cout<<e.what()<<std::endl;
                        }
                        catch(...)
                        {
                            std::cout<<"setMulti function error\n";
                        }
                    }*/
                    unsigned int minusHP=Dziadek.Update(Eq.HP,Eq.boostHP,przeladowanie.getElapsedTime(),Eq.w_rece);
                    if(Eq.boostHP!=0)
                    {
                        if(minusHP<=Eq.boostHP)
                            Eq.boostHP-=minusHP;
                        else
                        {
                            Eq.boostHP=0;
                            minusHP-=Eq.boostHP;
                            if(minusHP<=Eq.HP)
                                Eq.HP-=minusHP;
                        }
                    }else
                    if(minusHP<=Eq.HP)
                        Eq.HP-=minusHP;
                    else Eq.HP=0;
                    karabin.Update(Dziadek.posX,Dziadek.posY+30,Dziadek.getDegree(),&EnterPressed,Eq.w_rece);
                    if(level==1)
                    {
                        if(peppaEq.HP>0)
                            peppa.Update1(&peppaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(peppaEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(50);
                            odblokowane[1]=true;
                        }
                    }
                    if(level==2)
                    {
                        if(mamaEq.HP>0)
                            mama.Update2(&mamaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(mamaEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(70);
                            odblokowane[2]=true;
                        }
                    }
                    if(level==3)
                    {
                        if(mamaEq.HP>0)
                            mama.Update2(&mamaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(peppaEq.HP>0)
                            peppa.Update1(&peppaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(mamaEq.HP==0 && peppaEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(125);
                            odblokowane[3]=true;
                        }
                    }
                    if(level==4)
                    {
                        if(tataEq.HP>0)
                            tata.Update2(&tataEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(tataEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(140);
                            odblokowane[4]=true;
                        }
                    }
                    if(level==5)
                    {
                        if(tataEq.HP>0)
                            tata.Update2(&tataEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(peppaEq.HP>0)
                            peppa.Update1(&peppaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(tataEq.HP==0 && peppaEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(180);
                            odblokowane[5]=true;
                        }
                    }
                    if(level==6)
                    {
                        if(peppaEq.HP>0)
                            peppa.Update1(&peppaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(mamaEq.HP>0)
                            mama.Update2(&mamaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(tataEq.HP>0)
                            tata.Update2(&tataEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(tataEq.HP==0 && mamaEq.HP==0 && peppaEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(200);
                            odblokowane[6]=true;
                        }
                    }
                    if(level==7)
                    {
                        if(georgeEq.HP>0)
                            george.Update2(&georgeEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(georgeEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(220);
                            odblokowane[7]=true;
                        }
                    }
                    if(level==8)
                    {
                        if(georgeEq.HP>0)
                            george.Update2(&georgeEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(peppaEq.HP>0)
                            peppa.Update1(&peppaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(georgeEq.HP==0 && peppaEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(250);
                            odblokowane[8]=true;
                        }
                    }
                    if(level==9)
                    {
                        if(georgeEq.HP>0)
                            george.Update2(&georgeEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(peppaEq.HP>0)
                            peppa.Update1(&peppaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(mamaEq.HP>0)
                            mama.Update2(&mamaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(georgeEq.HP==0 && mamaEq.HP==0 && peppaEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(500);
                            odblokowane[9]=true;
                        }
                    }
                    if(level==10)
                    {
                        if(georgeEq.HP>0)
                            george.Update2(&georgeEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(peppaEq.HP>0)
                            peppa.Update1(&peppaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(mamaEq.HP>0)
                            mama.Update2(&mamaEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(tataEq.HP>0)
                            tata.Update2(&tataEq,&Eq.HP,&Eq.boostHP,Eq.w_rece,&Dziadek);
                        if(georgeEq.HP==0 && tataEq.HP==0 && mamaEq.HP==0 && peppaEq.HP==0)
                        {
                            level=0;
                            Eq.dodaj_za_zabojstwo(500);
                            //odblokowane[10]=true;
                        }
                    }
                }
                Misje_bt.Update(ButtonPressed);
                if(Menu_misje)
                {
                    Misja1_bt.Update(ButtonPressed);
                    Misja2_bt.Update(ButtonPressed);
                    Misja3_bt.Update(ButtonPressed);
                    Misja4_bt.Update(ButtonPressed);
                    Misja5_bt.Update(ButtonPressed);
                    Misja6_bt.Update(ButtonPressed);
                    Misja7_bt.Update(ButtonPressed);
                    Misja8_bt.Update(ButtonPressed);
                    Misja9_bt.Update(ButtonPressed);
                    Misja10_bt.Update(ButtonPressed);
                    for(short i=0;i<10;i++)
                        if(!odblokowane[i])
                            window.draw(lock[i]);
                }
            }
            Eq.Update(panelSklep,ButtonPressed);
            List.Update(ButtonPressed,&Eq);
            Sklep_bt.Update(ButtonPressed);
            saveBt.Update(ButtonPressed);
            loadBt.Update(ButtonPressed);
            if(interior==pociong)
                    Eq.pociag();
        }else
        {
            Eq.main.setLoop(false);
            window.draw(GameOver);
            Restart.Update(ButtonPressed);
            if(Restart.isPressed())
            {
                for(int i=0;i<10;i++)
                    odblokowane[i]=false;
                Eq.ammunition=15;
                Eq.HP=100;
                Eq.boostHP=0;
                return;
            }
        }
        window.display();
        poprz_klatka=klatka.getElapsedTime();
        klatka.restart();
    }
    EnterPressed=false;

    return;
}
