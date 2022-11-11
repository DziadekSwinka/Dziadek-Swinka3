#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdio>
#include "Saves.hpp"

void load(Equipment *Eq)
{
    std::fstream Allsave;
    std::string line="";
    Allsave.open("saves//allSaves.txt",std::ios::in);
    if(!Allsave.good())
        std::cout<<"Open file error"<<std::endl;
    int count=0;
    while(getline(Allsave,line))
    {
        count++;
    }
    std::fstream mySave;
    mySave.open("saves//save"+std::to_string(count)+".txt",std::ios::in);
    for(int i=0;i<7;i++)
    {
        getline(mySave,line);
        if(mySave.eof())
            break;
        /*switch(i)
        {
        case 0:
            Eq->ammunition=stoul(line);
            break;
        case 1:
            Eq->HP=stoul(line);
            break;
        case 2:
            Eq->pieniadze=stoul(line);
            break;
        case 3:
            {
            if(stoi(line)==1)
                Eq->pistolet=true;
            else
                Eq->pistolet=false;
            break;
            }

        case 4:
            {
            if(stoi(line)==1)
                Eq->karabin=true;
            else
                Eq->karabin=false;
            break;
            }
        case 5:
            {
            if(stoi(line)==1)
                Eq->bazooka=true;
            else
                Eq->bazooka=false;
            break;
            }
        case 6:
            {
            if(stoi(line)==1)
                Eq->uzi=true;
            else
                Eq->uzi=false;
            break;
            }
        default: break;
        }*/
    }
    mySave.close();
    std::cout<<Eq->ammunition<<std::endl;
    std::cout<<Eq->HP<<std::endl;
    std::cout<<Eq->pieniadze<<std::endl;
    std::cout<<Eq->pistolet<<std::endl;
    std::cout<<Eq->karabin<<std::endl;
    std::cout<<Eq->bazooka<<std::endl;
    std::cout<<Eq->uzi<<std::endl;
}

void save(Equipment *Eq)
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
