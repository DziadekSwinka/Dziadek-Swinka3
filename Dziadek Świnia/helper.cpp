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
}
void helper::Update(int state)
{
    if(state==0)
    {

    }else if(state>0)
        disp_text.setString(Mem_text[state-1]);
}
