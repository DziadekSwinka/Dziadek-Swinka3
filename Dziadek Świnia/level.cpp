#include "level.hpp"

void level_setUp(unsigned short level,Equipment *Eq,AI_Eq *peppa)
{
    resetuj();
    Eq->HP=100;
    switch (level)
    {
    case 0:

        break;
    case 1:
        level1(peppa);          //na moje powinno byæ &peppa, ale nie bede klucil sie z kompilatorem
        break;
    case 2:
        break;
    case 3:
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
