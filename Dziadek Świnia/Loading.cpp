#include "Loading.hpp"

LoadingScreen::LoadingScreen(sf::RenderWindow &window1):window(window1),p(0)
{
    bg.loadFromFile("Textures//Title.png");
    BG.setTexture(bg);
    Front=new sf::RectangleShape(sf::Vector2f(0,50));
    Back=new sf::RectangleShape(sf::Vector2f(800,50));
    Left=new sf::CircleShape(25);
    Right=new sf::CircleShape(25);
    Front->setPosition(560,800);
    Back->setPosition(560,800);
    Left->setPosition(535,800);
    Right->setPosition(1335,800);
}
void LoadingScreen::Push()
{
    p+=10;
    if(p>=5)
        Left->setFillColor(sf::Color::Red);
    else
        Left->setFillColor(sf::Color::White);
    if(p>=95)
        Right->setFillColor(sf::Color::Red);
    else
        Right->setFillColor(sf::Color::White);
    Front->setSize(sf::Vector2f(8*p,50));
    window.clear();
    window.draw(BG);
    window.draw(*Back);
    window.draw(*Front);
    window.draw(*Left);
    window.draw(*Right);
    window.display();
}
