#ifndef LEVEL_HPP_INCLUDED
#define LEVEL_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "Equipment.hpp"
#include "side.hpp"

class bullet;

struct AI_Eq
{
    unsigned int HP=100;
    bullet* bullet_wsk[10]={nullptr};
};
void level_setUp(unsigned short level,Equipment *Eq,AI_Eq *peppa,AI_Eq *mama);
void resetuj();
void level1(AI_Eq *peppa);
void level2(AI_Eq *mama);
void level3(AI_Eq *mama,AI_Eq *peppa);



#endif // LEVEL_HPP_INCLUDED
