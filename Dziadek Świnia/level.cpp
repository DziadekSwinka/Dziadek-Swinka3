#include "level.hpp"


void level_setUp(unsigned short level,Equipment *Eq,AI_Eq *peppa,AI_Eq *mama,AI_Eq *tata,AI_Eq *george)
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
        level4(tata);
        break;
    case 5:
        level5(tata,peppa);
        break;
    case 6:
        level6(mama,tata,peppa);
        break;
    case 7:
        level7(george);
        break;
    case 8:
        level8(george,peppa);
        break;
    case 9:
        level9(george,mama,peppa);
        break;
    case 10:
        level10(mama,tata,peppa,george);
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
void level4(AI_Eq *tata)
{
    //tata z karabinem
    tata->HP=100;
}
void level5(AI_Eq *tata,AI_Eq *peppa)
{
    tata->HP=100;
    peppa->HP=100;
}
void level6(AI_Eq *mama,AI_Eq *tata,AI_Eq *peppa)
{
    tata->HP=100;
    mama->HP=100;
    peppa->HP=100;
}
void level7(AI_Eq *george)
{
    george->HP=100;
}
void level8(AI_Eq *george,AI_Eq *peppa)
{
    george->HP=100;
    peppa->HP=100;
}
void level9(AI_Eq *george,AI_Eq *mama,AI_Eq *peppa)
{
    peppa->HP=100;
    mama->HP=100;
    george->HP=100;
}
void level10(AI_Eq *mama,AI_Eq *tata,AI_Eq *peppa,AI_Eq *george)
{
    peppa->HP=100;
    mama->HP=100;
    george->HP=100;
    tata->HP=100;
}
