#ifndef SEZON_H_INCLUDED
#define SEZON_H_INCLUDED

#include <string>

std::string set_sezon()
{
    std::string sezon="";
    time_t t = time(nullptr);
    struct tm Tm = *localtime(&t);
    if(Tm.tm_mon==9 || Tm.tm_mon==11 || Tm.tm_mon==10 || Tm.tm_mon==0)
    {
        sezon="_winter";
    }else sezon="";
    return sezon;
}

#endif // SEZON_H_INCLUDED
