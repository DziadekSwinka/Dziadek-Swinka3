#include <ctime>
#include <fstream>
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include "Saves.hpp"

saveList::saveList(sf::RenderWindow &window1,float stosX,float stosY):window(window1),stosX(stosX),stosY(stosY)
{
    rectangle.setSize(sf::Vector2f(1190.f/stosX,790.f/stosY));
    rectangle.setFillColor(sf::Color(160,140,80));
    rectangle.setOutlineColor(sf::Color(70,70,70));
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(360.f/stosX,100.f/stosY);
}
void saveList::Update()
{
    if(showList)
    {
        std::vector<button*>LoadButton;
        int ile=LoadList();
        LoadButton.reserve(ile);
        for(int i=0;i<ile;i++)
        {
            LoadButton=new button(window,"Textures//GUI//noneText","Textures//GUI//noneTextc",1200.f*stosX,(160(+130*i)*stosY),stosX,stosY);
        }
        window.draw(rectangle);
    }
}
unsigned int saveList::LoadList()
{
    std::fstream Allsave;
    std::string line="";
    Allsave.open("saves//allSaves.txt",std::ios::in);
    if(!Allsave.good())
    {
        std::cout<<"Open file error"<<std::endl;
        return 0;
    }
    int count=0;
    while(getline(Allsave,line))
    {
        count++;
    }
    return count;
}
void saveList::load(Equipment *Eq,int i)
{

    std::string line="";
    std::fstream mySave;
    mySave.open("saves//save"+std::to_string(i)+".txt",std::ios::in);
    if(!mySave.good())
    {
        std::cout<<"Save file error";
        return;
    }

    int j=0;
    while(getline(mySave,line))
    {
        //std::cout<<line<<std::endl;
        switch(j)
        {
        case 0:
            Eq->ammunition=stoi(line);
            break;
        case 1:
            Eq->HP=stoi(line);
            break;
        case 2:
            Eq->pieniadze=stoi(line);
            break;
        case 3:
            {
            if(static_cast<int>(line[0])==49)
                Eq->pistolet=true;
            else
                Eq->pistolet=false;
            break;
            }
        case 4:
            {
            if(static_cast<int>(line[0])==49)
                Eq->karabin=true;
            else
                Eq->karabin=false;
            break;
            }
        case 5:
            {
            if(static_cast<int>(line[0])==49)
                Eq->bazooka=true;
            else
                Eq->bazooka=false;
            break;
            }
        case 6:
            {
            if(static_cast<int>(line[0])==49)
                Eq->uzi=true;
            else
                Eq->uzi=false;
            break;
            }
        default: break;
        }
        i++;
    }
    mySave.close();
    /*std::cout<<Eq->ammunition<<std::endl;
    std::cout<<Eq->HP<<std::endl;
    std::cout<<Eq->pieniadze<<std::endl;
    std::cout<<Eq->pistolet<<std::endl;
    std::cout<<Eq->karabin<<std::endl;
    std::cout<<Eq->bazooka<<std::endl;
    std::cout<<Eq->uzi<<std::endl;*/
}

void saveList::save(Equipment *Eq)
{
    std::fstream Allsave;
    std::string name="",content="",line="";
    Allsave.open("saves//allSaves.txt",std::ios::in);
    if(!Allsave.good())
        std::cout<<"Open file error"<<std::endl;
    int count=0;
    while(getline(Allsave,line))
    {
        content+=line+"\n";
        count++;
    }
    name+=content;
    name+="save"+std::to_string(count);
    Allsave.close();
    Allsave.open("saves//allSaves.txt",std::ios::out|std::ios::trunc);
    Allsave.write(& name[0],name.length());
    Allsave.close();
    std::fstream mySave;
    content="";
    content+=std::to_string(Eq->ammunition)+"\n";
    content+=std::to_string(Eq->HP)+"\n";
    content+=std::to_string(Eq->pieniadze)+"\n";
    content+=std::to_string(Eq->pistolet)+"\n";
    content+=std::to_string(Eq->karabin)+"\n";
    content+=std::to_string(Eq->bazooka)+"\n";
    content+=std::to_string(Eq->uzi)+"\n";
    mySave.open("saves//save"+std::to_string(count)+".txt",std::ios::out|std::ios::trunc);
    mySave.write(& content[0],content.length());
    mySave.close();
}
