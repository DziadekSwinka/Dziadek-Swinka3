#include "helper.hpp"

helper::helper(sf::RenderWindow &temp_window): window(temp_window),
                                                board(sf::Vector2f(1000,72))
{
    std::fstream file;
    file.open("helper.txt");
    while(!file.eof())
    {
        std::string temp;
        getline(file,temp);
        Mem_text.push_back(temp);
    }
    file.close();

    boardPosition[0]=1920.f/2.f;

    font.loadFromFile("Fonts//Oswald-Regular.ttf");
    disp_text.setOrigin(board.getSize().x/2,0);
    disp_text.setFont(font);
    disp_text.setCharacterSize(24);
    disp_text.setPosition(boardPosition[0]+24,boardPosition[1]+24);
    disp_text.setColor(sf::Color::Black);

    board.setFillColor(sf::Color(180,180,180));
    board.setOutlineColor(sf::Color(135,135,135));
    board.setOutlineThickness(5);
    board.setOrigin(board.getSize().x/2,0);
    board.setPosition(boardPosition[0],boardPosition[1]);
}
void helper::SetState(int temp_state)
{
    if(temp_state>state)
    {
        isSet=true;
        clock.restart();
        state=temp_state;
    }
}
void helper::Update()
{
    time=clock.getElapsedTime();
    if(state==0)
    {

    }else if(state>0)
        disp_text.setString(Mem_text[state-1]);

    if(time.asSeconds()<3 && isSet)
    {
        window.draw(board);
        window.draw(disp_text);
    }
    else if(isSet) isSet=false;
}
