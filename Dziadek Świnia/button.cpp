#include "button.hpp"

button::button(sf::RenderWindow &window1,std::string sciezka,std::string sciezka2,float x,float y):window(window1)
{
    txt.loadFromFile(sciezka);
    txt2.loadFromFile(sciezka2);
    Button.setTexture(txt);
    Button.setPosition(x,y);
    scaleX=0.6;
    scaleY=0.6;
    Button.setScale(scaleX,scaleY);
}
void button::Update(bool ButtonPressed)
{
    time=clock.getElapsedTime();
    sf::Vector2i Mouse = sf::Mouse::getPosition( window );
    Button.setScale(scaleX,scaleY);
    float szerokosc=txt.getSize().x*Button.getScale().x;
    float wysokosc=txt.getSize().y*Button.getScale().y;
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
    if(onclick && time.asSeconds()>0.2)
    {
        clock.restart();
        return true;
    }
    return false;
}
