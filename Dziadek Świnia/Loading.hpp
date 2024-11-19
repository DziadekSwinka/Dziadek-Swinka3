#ifndef LOADING_HPP_INCLUDED
#define LOADING_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class LoadingScreen
{
public:
    void Push();
    int p;
    LoadingScreen(sf::RenderWindow &window1);
private:

    sf::RenderWindow &window;
    sf::RectangleShape *Front;
    sf::RectangleShape *Back;
    sf::CircleShape *Left,*Right;
    sf::Texture bg;
    sf::Sprite BG;
};

#endif // LOADING_H_INCLUDED
