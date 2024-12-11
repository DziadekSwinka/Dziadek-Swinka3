#ifndef SAVES_HPP_INCLUDED
#define SAVES_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include "Equipment.hpp"
#include "button.hpp"

class Equipment;

class saveList
{
private:
    sf::Font OswaldRegular;
    sf::Text text[6][6];
    float stosX,stosY;
    sf::RenderWindow &window;
    sf::RectangleShape rectangle;
    button Bt[36]={ button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",(500.f*stosX),(160+(130*0)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",(500.f*stosX),(160+(130*1)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",(500.f*stosX),(160+(130*2)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",(500.f*stosX),(160+(130*3)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",(500.f*stosX),(160+(130*4)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",(500.f*stosX),(160+(130*5)*stosY),stosX,stosY),

                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*1))*stosX),(160+(130*0)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*1))*stosX),(160+(130*1)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*1))*stosX),(160+(130*2)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*1))*stosX),(160+(130*3)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*1))*stosX),(160+(130*4)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*1))*stosX),(160+(130*5)*stosY),stosX,stosY),

                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*2))*stosX),(160+(130*0)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*2))*stosX),(160+(130*1)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*2))*stosX),(160+(130*2)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*2))*stosX),(160+(130*3)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*2))*stosX),(160+(130*4)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*2))*stosX),(160+(130*5)*stosY),stosX,stosY),

                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*3))*stosX),(160+(130*0)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*3))*stosX),(160+(130*1)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*3))*stosX),(160+(130*2)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*3))*stosX),(160+(130*3)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*3))*stosX),(160+(130*4)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*3))*stosX),(160+(130*5)*stosY),stosX,stosY),

                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*4))*stosX),(160+(130*0)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*4))*stosX),(160+(130*1)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*4))*stosX),(160+(130*2)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*4))*stosX),(160+(130*3)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*4))*stosX),(160+(130*4)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*4))*stosX),(160+(130*5)*stosY),stosX,stosY),

                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*5))*stosX),(160+(130*0)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*5))*stosX),(160+(130*1)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*5))*stosX),(160+(130*2)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*5))*stosX),(160+(130*3)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*5))*stosX),(160+(130*4)*stosY),stosX,stosY),
                    button(window,"Textures//GUI//noneText.png","Textures//GUI//noneTextc.png",((500.f+(150*5))*stosX),(160+(130*5)*stosY),stosX,stosY)};

public:
    unsigned int LoadList();
    void load(Equipment *Eq,int i,unsigned int *state,bool unlock[]);
    void save(Equipment *Eq,int state,bool unlock[]);
    bool showList;
    saveList(sf::RenderWindow &window1,float stosX,float stosY);
    void Update(bool Bp,Equipment *Eq,unsigned int *state,bool unlock[]);
};

#endif // SAVES_HPP_INCLUDED
