#include "level.hpp"


void level_setUp(unsigned short level,Equipment *Eq,AI_Eq *peppa,AI_Eq *mama)
{
    resetuj();
    Eq->HP=100;
    switch (level)
    {
    case 0:
        break;
    case 1:
        level1(peppa);  //na moje powinno byæ &peppa, ale nie bede klucil sie
        break;
    case 2:
        level2(mama);
        break;
    case 3:
        level3(mama,peppa);
        break;
    case 4:
        break;

    }
}
void resetuj()
{
    ///kasowanie wszystkich obiektow nalezacych do poziomow


}
void level1(AI_Eq *peppa)
{
    //swinka z nozem
    peppa->HP=100;
}
void level2(AI_Eq *mama)
{
    //mama z pistoletem
    mama->HP=100;
}
void level3(AI_Eq *mama,AI_Eq *peppa)
{
    //mama z pistoletem i peppa z nozem
    mama->HP=100;
    peppa->HP=100;
}
