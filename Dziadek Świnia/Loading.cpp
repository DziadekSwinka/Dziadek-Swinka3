#include "Loading.hpp"

LoadingScreen::LoadingScreen(sf::RenderWindow &window1):window(window1),p(0)
{
    bg.loadFromFile("Textures//Background//Title.png");
    BG.setTexture(bg);
    Front=new sf::RectangleShape(sf::Vector2f(0,50));
    Back=new sf::RectangleShape(sf::Vector2f(800,50));
    Left=new sf::CircleShape(25);
    Right=new sf::CircleShape(25);
    Front->setPosition(560,700);
    Back->setPosition(560,700);
    Left->setPosition(535,700);
    Right->setPosition(1335,700);
    Front->setFillColor(sf::Color::Red);
    Back->setFillColor(sf::Color::White);
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
