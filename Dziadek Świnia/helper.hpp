#ifndef HELPER_HPP_INCLUDED
#define HELPER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

class helper
{
private:
    sf::RenderWindow &window;
    sf::RectangleShape board;
    sf::Text disp_text;
    sf::Font font;
    std::vector<std::string>Mem_text;
public:
    helper(sf::RenderWindow &temp_window);
    void Update(int state);
};

#endif // HELPER_HPP_INCLUDED
