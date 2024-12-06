#include "Background.hpp"

Background::Background(sf::RenderWindow &window1,std::string sciezka,float x1,std::string budynek1,float x2,std::string budynek2,float x3,std::string budynek3,float stosX,float stosY,std::string sezon):stosX(stosX),stosY(stosY),window(window1)
{

    srand(time(NULL));
    tloGra.setSize(sf::Vector2f(stosX*1920,stosY*1080));
    tloGra.setFillColor(sf::Color(76,76,76));
    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    gertruda.loadFromFile("Textures//Background//gertruda.png");
    chmura.loadFromFile("Textures//Background//cloud.png");
    baza.loadFromFile("Textures//Background//baza.png");
    wsk.loadFromFile("Textures//GUI//wskaznik.png");
    mStruct.texture.loadFromFile("Textures//Charakters//Dinozar"+sezon+".png");
    for(int i=0;i<5;i++)
    {
        mStruct.target[i].setScale(0.5/stosX,0.5/stosY);
        mStruct.target[i].setTexture(mStruct.texture);
    }
    Wskaznik.setTexture(wsk);
    Wskaznik.setOrigin(8,8);
    Wskaznik.setScale(2,2);
    Baza.setTexture(baza);
    Chmura.setTexture(chmura);
    Chmura.setScale(0.3,0.3);
    Chmura.setPosition(300,200);
    Pociag.setTexture(gertruda);
    Pociag.setPosition(600,500);
    text.setFont(OswaldRegular);
    text.setCharacterSize(20);
    text.setColor(sf::Color(25,60,210));
    b1_x=x1;
    b2_x=x2;
    b3_x=x3;
    txt.loadFromFile(sciezka+sezon+".png");
    b1.loadFromFile(budynek1+sezon+".png");
    B1.setTexture(b1);
    B1.setScale(0.5,0.5);
    B1.setOrigin(0,b1.getSize().y);
    b2.loadFromFile(budynek2+sezon+".png");
    B2.setTexture(b2);
    B2.setScale(0.5,0.5);
    B2.setOrigin(0,b2.getSize().y);
    b3.loadFromFile(budynek3+sezon+".png");
    B3.setTexture(b3);
    B3.setScale(0.5,0.5);
    B3.setOrigin(0,b3.getSize().y);
    for(int i=0;i<3;i++)
    {
        bcg[i].setTexture(txt);
        bcg[i].setScale(2/stosX,2/stosY);

    }
    bcg[0].setPosition(0-798,window.getSize().y-(txt.getSize().y*1.7*bcg[0].getScale().y/2));
    bcg[1].setPosition(0,window.getSize().y-(txt.getSize().y*1.7*bcg[0].getScale().y/2));
    bcg[2].setPosition(window.getSize().x-4,window.getSize().y-(txt.getSize().y*1.7*bcg[0].getScale().y/2));
    if(snieg.loadFromFile("Textures//Items//"+sezon+"snow.png"))
    {
        snowFall=true;
        for(int i=0;i<100;i++)
        {
            Snieg[i].setTexture(snieg);
            Snieg[i].setPosition(std::rand()%window.getSize().x,std::rand()%window.getSize().y);
        }
    }else
        snowFall=false;

}
void Background::wyswietl_napis(float z1,float z2,float z3)
{
    text.setString("WEJDZ DO BUDYNKU [F]");

    if(abs(x+z1-700)<200)
    {
        text.setPosition(x+z1+80,300);
        pokaz_tekst[0]=1;
    }else pokaz_tekst[0]=0;

    if(abs(x+z3-700)<200)
    {
        text.setPosition(x+z3+180,300);
        pokaz_tekst[1]=1;
    }else pokaz_tekst[1]=0;

    if(abs(x+z2-700)<200)
    {
        text.setPosition(x+z2+60,300);
        pokaz_tekst[2]=1;
    }else pokaz_tekst[2]=0;
}
void Background::wejdz(Interior *interior,bool *panelSklep)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        if(pokaz_tekst[0])
        {
            *interior=tajna_baza_wojskowa_pod_domem;
            x_outside=x;
        }else if(pokaz_tekst[1])
        {
            *interior=pociong;
            x_outside=x;
        }else if(pokaz_tekst[2])
        {
            *panelSklep=true;
            x_outside=x;
        }
    }
}
unsigned int Background::miniGra()
{
    short zwroc=0;
    const int WinX=window.getSize().x;
    const int WinY=window.getSize().y;
    mStruct.time=mStruct.clock.getElapsedTime();
    if(mStruct.time.asSeconds()>=1/mStruct.speed)
    {
        mStruct.clock.restart();
        for(short i=0;i<5;i++)
        {
            mStruct.target_pos[i].x=(std::rand()%WinX-100/stosX)+100/stosX;
            mStruct.target_pos[i].y=(std::rand()%static_cast<int>(WinY-200/stosY)+300.f/stosY);
            mStruct.target[i].setPosition(mStruct.target_pos[i]);
            mStruct.display[i]=true;
        }
    }
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    for(short i=0;i<5;i++)
    {
        if(mousePos.x>mStruct.target_pos[i].x && mousePos.x<mStruct.target_pos[i].x+mStruct.texture.getSize().x*mStruct.target[i].getScale().x)
        {
            if(mousePos.y>mStruct.target_pos[i].y && mousePos.y<mStruct.target_pos[i].y+mStruct.texture.getSize().y*mStruct.target[i].getScale().y)
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && mStruct.display[i]==true)
                {
                    zwroc+=3;
                    mStruct.speed+=0.001;
                    mStruct.display[i]=false;
                    continue;
                }
            }
        }
    }
    window.draw(tloGra);
    for(short m=0;m<5;m++)
        if(mStruct.display[m]==true)
            window.draw(mStruct.target[m]);
    window.draw(Wskaznik);
    return zwroc;
}
void Background::renderSnow(float deltaTime)
{
    for(int i=0;i<100;i++)
    {
        if(std::rand()%(i+1)==i+1)
        {
            continue;
        }
        if(Snieg[i].getPosition().y>window.getSize().y)
        {
            Snieg[i].setPosition(std::rand()%window.getSize().x,0);
        }
        Snieg[i].move(0,0.2*deltaTime);
    }
}
unsigned int Background::Update(Interior *interior,unsigned short level,bool *panelSklep,bool EnterPressed,float deltaTime,bool key)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        *interior=outside;
        x=x_outside;
        mGra=false;
        EnterPressed=false;
    }
    wyswietl_napis(b1_x,b2_x,b3_x);
    wejdz(interior,panelSklep);
    window.draw(Chmura);
    if(*interior==outside || *interior==pociong)
    {
        if(true==sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            background_move(Right);
        if(true==sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && *interior!=pociong)
            background_move(Left);
        B1.setPosition(x-b1_x,750);
        B2.setPosition(x-b2_x,750);
        B3.setPosition(x-b3_x,750);
        for(short i=0;i<3;i++)
                bcg[i].setTexture(txt);
        if(*interior==outside)
        {
            window.draw(B1);
            window.draw(B2);
            window.draw(B3);
            if(pokaz_tekst[0]||pokaz_tekst[1]||pokaz_tekst[2])
                if(level<1)
                    window.draw(text);
        }
        window.draw(bcg[0]);
        window.draw(bcg[1]);
        window.draw(bcg[2]);
        if(snowFall==true)
        {
            renderSnow(deltaTime);
            for(int i=0;i<100;i++)
            {
                if(Snieg[i].getPosition().y<=bcg[1].getPosition().y)
                    window.draw(Snieg[i]);
            }
        }
        if(*interior==pociong)
        {
            window.draw(Pociag);
        }
    }
    unsigned int p=0.f;
    if(*interior==tajna_baza_wojskowa_pod_domem)
    {
        sf::Vector2i mysz=sf::Mouse::getPosition(window);
        Wskaznik.setPosition(static_cast<sf::Vector2f>(mysz));

        window.draw(Baza);

        if(mGra==true)
        {
            p=miniGra();
        }
    }
    if(EnterPressed==true && mGra==false)
    {
        if(key)
            mGra=true;
        else
        {
            //wejscie tylko z kluczem - dorobic napis
        }
    }
    return p;
}

bool Background::background_move(side Side)
{
    for(int i=0;i<3;i++)
    {
        if(Side==Left)
        {
            bcg[i].move(0.2*czas_na_klatke(),0);
            Chmura.move(0.02*czas_na_klatke(),0);
            x+=0.2*czas_na_klatke()*1.4;
        }
        if(Side==Right)
        {
            bcg[i].move(-0.2*czas_na_klatke(),0);
            Chmura.move(-0.02*czas_na_klatke(),0);
            x-=0.2*czas_na_klatke()*1.4;
        }

    }
    if(Chmura.getPosition().x>window.getSize().x+200)
        Chmura.setPosition(-100,200);
    if(Chmura.getPosition().x<-200)
        Chmura.setPosition(window.getSize().x+100,200);

    if((bcg[2].getPosition().x)<0)
        {
            bcg[0].setPosition(0-798,window.getSize().y-(txt.getSize().y*1.7*bcg[0].getScale().y/2));
            bcg[1].setPosition(0,window.getSize().y-(txt.getSize().y*1.7*bcg[0].getScale().y/2));
            bcg[2].setPosition(window.getSize().x-4,window.getSize().y-(txt.getSize().y*1.7*bcg[0].getScale().y/2));
        }
    if((bcg[0].getPosition().x)>0)
        {
            bcg[0].setPosition(0-798,window.getSize().y-(txt.getSize().y*1.7*bcg[0].getScale().y/2));
            bcg[1].setPosition(0,window.getSize().y-(txt.getSize().y*1.7*bcg[0].getScale().y/2));
            bcg[2].setPosition(window.getSize().x-4,window.getSize().y-(txt.getSize().y*1.7*bcg[0].getScale().y/2));
        }

    return true;
}


