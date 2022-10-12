#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class button
{
private:
    sf::RenderWindow &window;
    sf::Texture txt,txt2;
    sf::Sprite Button;
    sf::Clock clock;
    sf::Time time;
    bool onclick=false;
public:
    button(sf::RenderWindow &window1,std::string sciezka,std::string sciezka2,float x,float y,float sX,float sY);
    void Update(bool ButtonPressed);
    bool isPressed();
    float scaleX,scaleY;
};

#endif // BUTTON_HPP_INCLUDED
