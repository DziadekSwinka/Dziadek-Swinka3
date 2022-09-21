#include "level.hpp"

void level_setUp(unsigned short level,Equipment *Eq)
{
    resetuj();
    Eq->HP=100;
    switch (level)
    {
    case 0:

        break;
    case 1:
        level1();
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
void level1()
{
    //swinka z nozem
}
