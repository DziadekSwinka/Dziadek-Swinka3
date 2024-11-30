#include "helper.hpp"

helper::helper(sf::RenderWindow &temp_window):window(temp_window)
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

    font.loadFromFile("Fonts//Oswald-Regular.ttf");
    disp_text.setFont(font);
    disp_text.setCharacterSize(24);
    disp_text.setPosition(200,200);
}
void helper::SetState(int temp_state)
{
    isSet=true;
    clock.restart();
    state=temp_state;
}
void helper::Update()
{
    time=clock.getElapsedTime();
    if(state==0)
    {

    }else if(state>0)
        disp_text.setString(Mem_text[state-1]);

    if(time.asSeconds()<10)
        window.draw(disp_text);
    else if(isSet) isSet=false;
}
