#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "side.hpp"
#include "Equipment.hpp"
#include "obsluga_broni.hpp"

//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
bool ButtonPressed=0;
bool EnterPressed=0;

enum Mode
{
    lev1,           //
    lev2,           //
    lev3,           //
    lev4,           //
    without_level
};
enum Interior
{
    shop,
    home,
    outside
};
Interior interior;

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
private:
    sf::RenderWindow &window;
    sf::Texture txt;
    sf::Sprite postac;
    void Fall();
    void move_to_side(side Side);
    float vs=0;
    float hand_degree=0;
public:
    Postac(sf::RenderWindow &window1,std::string sciezka,float x,float y);
    void Update();
    float getDegree();
    float posX,posY;
};
Postac::Postac(sf::RenderWindow &window1,std::string sciezka,float x,float y):window(window1)
{
    txt.loadFromFile(sciezka);
    postac.setTexture(txt);
    postac.setScale(0.5,0.5);
    postac.setOrigin((txt.getSize().x)/4,(txt.getSize().y)/4);
    postac.setPosition(x,y);
    posX=x;
    posY=y;
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
void Postac::Update()
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        hand_degree+=0.2;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        hand_degree-=0.2;
    window.draw(postac);
    posX=postac.getPosition().x;
    posY=postac.getPosition().y;
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


//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    sf::RenderWindow window(sf::VideoMode(1920,1080), "Dziadek Œwinka");
    interior=outside;
    const int GroundLevel=700;
    bool Menu_misje=false;

    Postac Dziadek(window,"Textures//dziadek.png",window.getSize().x/2,GroundLevel);
    Background background(window,"Textures//grass.png",100,"Textures//grandpahouse.png",-800,"Textures//house.png",900,"Textures//shop.png");
    button Misje_bt(window,"Textures//bm.png","Textures//bmc.png",100,50);
    button Misja1_bt(window,"Textures//m1.png","Textures//m1c.png",400,10);
    button Misja2_bt(window,"Textures//m2.png","Textures//m2c.png",400,110);
    bron karabin(window,"Textures//ak47.png",1);
    Equipment Eq(window);
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
        window.clear(sf::Color(138,191,255));
        background.Update();
        Dziadek.Update();
        //std::cout<<EnterPressed<<std::endl;
        karabin.Update(Dziadek.posX,Dziadek.posY,Dziadek.getDegree(),&EnterPressed);
        Eq.Update();
        //Misje_bt.Update();
        if(Menu_misje)
        {
            //Misja1_bt.Update();
        }
        if(Menu_misje)
        {
            //Misja2_bt.Update();
        }

        window.display();
    }
    EnterPressed=false;
    return 0;
}
