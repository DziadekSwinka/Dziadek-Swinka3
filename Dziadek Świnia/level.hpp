#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Equipment.hpp"

struct AI_Eq
{
    unsigned int HP=100;
};

void level_setUp(unsigned short level,Equipment *Eq,AI_Eq *peppa);
void resetuj();
void level1(AI_Eq *peppa);



#endif // LEVEL_HPP_INCLUDED
