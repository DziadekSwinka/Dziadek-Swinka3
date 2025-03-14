#ifndef HELPER_HPP_INCLUDED
#define HELPER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <queue>

class helper
{
private:
    float boardPosition[2]={150,900};
    sf::RenderWindow &window;
    sf::RectangleShape board;
    sf::Text disp_text;
    sf::Font font;
    sf::Clock clock;
    sf::Time time;
    std::vector <std::string> Mem_text;
    std::queue <int> que;
    int state;

public:
    bool isSet=false;
    helper(sf::RenderWindow &temp_window);
    void SetState(int temp_state);
    void Update();
};

#endif // HELPER_HPP_INCLUDED
