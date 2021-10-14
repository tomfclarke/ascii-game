#include "../include/enemy.h"

Enemy::Enemy()
{
    loc.x = 0;
    loc.y = 0;

    prevLoc = loc;

    appearance = '�';
}
