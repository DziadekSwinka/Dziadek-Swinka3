#include <ctime>
#include <fstream>
#include <string>
#include <iostream>

#include "Saves.hpp"

saveList::saveList(sf::RenderWindow &window1,float stosX,float stosY):window(window1),stosX(stosX),stosY(stosY)
{
    showList=false;
    OswaldRegular.loadFromFile("Fonts//Oswald-Regular.ttf");
    rectangle.setSize(sf::Vector2f(1190.f/stosX,790.f/stosY));
    rectangle.setFillColor(sf::Color(160,140,80));
    rectangle.setOutlineColor(sf::Color(70,70,70));
    rectangle.setOutlineThickness(5);
    rectangle.setPosition(360.f/stosX,100.f/stosY);
    int k=0;
    for(int i=0;i<6;i++)
        for(int j=0;j<6;j++)
        {
            text[i][j].setFont(OswaldRegular);
            text[i][j].setPosition((530+(150*j))*stosX,(170+(130*i))*stosY);
            text[j][i].setString("Save "+std::to_string(k));
            k++;
        }

}
void saveList::Update(bool Bp,Equipment *Eq,unsigned int *state,bool unlock[])
{
    if(showList)
    {
        window.draw(rectangle);
        int ile=LoadList();
        for(int i=0;i<ile && i<36;i++)
        {
            Bt[i].Update(Bp);

            int k=0;
            for(int i=0;i<6;i++)
                for(int j=0;j<6;j++)
                {
                    if(k<ile)
                        window.draw(text[j][i]);
                    k++;
                }

            if(Bt[i].isPressed())
                load(Eq,i,state,unlock);
        }
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
    Allsave.close();
    Allsave.clear();
    return count;
}
void saveList::load(Equipment *Eq,int i,unsigned int *state,bool unlock[])
{

    std::string line="";
    std::fstream mySave;
    std::cout<<"saves//save"+std::to_string(i)+".txt"<<std::endl;
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
        case 7:
            {
            Eq->beer=stoi(line);
            break;
            }
        case 8:
            {
                *state=stoi(line);
                break;
            }
        case 9:
            {
                int k=0;
                while(stoi(line)>k)
                {
                    unlock[j]=true;
                    k++;
                }
            }
        default: break;
        }
        j++;
    }
    mySave.close();
}

void saveList::save(Equipment *Eq,int state,bool unlock[])
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
    content+=std::to_string(Eq->beer)+"\n";
    content+=std::to_string(state)+"\n";
    int j=0;
    while(unlock[j]==true)
    {
        j++;
    }
    content+=std::to_string(j)+"\n";
    mySave.open("saves//save"+std::to_string(count)+".txt",std::ios::out|std::ios::trunc);
    mySave.write(& content[0],content.length());
    mySave.close();
}
