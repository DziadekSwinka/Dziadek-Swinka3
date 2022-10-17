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
void level_setUp(unsigned short level,Equipment *Eq,AI_Eq *peppa,AI_Eq *mama,AI_Eq *tata,AI_Eq *george);
void resetuj();
void level1(AI_Eq *peppa);
void level2(AI_Eq *mama);
void level3(AI_Eq *mama,AI_Eq *peppa);
void level4(AI_Eq *tata);
void level5(AI_Eq *tata,AI_Eq *peppa);
void level6(AI_Eq *mama,AI_Eq *tata,AI_Eq *peppa);
void level7(AI_Eq *george);
void level8(AI_Eq *george,AI_Eq *peppa);
void level9(AI_Eq *george,AI_Eq *mama,AI_Eq *peppa);
void level10(AI_Eq *mama,AI_Eq *tata,AI_Eq *peppa,AI_Eq *george);



#endif // LEVEL_HPP_INCLUDED
