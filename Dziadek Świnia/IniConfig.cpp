#include "IniConfig.hpp"
#include <iostream>
/*
Zapis:

    WritePrivateProfileString("sekcja1","nazwa","wartoœæ","c:\\plik.ini");

odczyt:

    char buf[256];
    GetPrivateProfileString("sekcja1","nazwa","domyœlnie",buf,256,"c:\\plik.ini");
*/
void config()
{
    /*char **buf=new char*[10];       //10 charow do kazdej linijki
    for(int i=0;i<10;i++)
        buf[i]=new char[256];*/
    char buf[9][256];
    /*for(int i=0;i<9;i++)
        for(int j=0;i<256;j++)
            buf[i][j]=0;*/
    GetPrivateProfileString("Window","Size","1920x1080",buf[0],256,"config.ini");
    GetPrivateProfileString("Window","Frame Limit","0",buf[1],256,"config.ini");
    GetPrivateProfileString("Window","Antyaliasing","8",buf[2],256,"config.ini");
    GetPrivateProfileString("Volume","Master","10",buf[3],256,"config.ini");
    GetPrivateProfileString("Volume","Music","20",buf[4],256,"config.ini");
    GetPrivateProfileString("Volume","Main charakter","50",buf[5],256,"config.ini");
    GetPrivateProfileString("Volume","Shot","1",buf[6],256,"config.ini");
    GetPrivateProfileString("Volume","Other charakters","40",buf[7],256,"config.ini");
    iniToSetup(buf);
}
void iniToSetup(char buf[9][256])
{
    std::string stringBuf[9]={"","","","","","","","",""};
    for(int i=0;i<9;i++)
        for(int j=0;j<256;j++)
            stringBuf[i]+=buf[i][j];
    for(int i=0;i<7;i++)
    {
        try
        {
            lineToSetup(stringBuf[i],i);
        }
        catch(...)
        {
            std::cout<<"Error '.ini' file in line"<<i<<std::endl;
        }
    }
}
