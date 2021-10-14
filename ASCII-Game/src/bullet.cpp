#include "../include/bullet.h"

Bullet::Bullet()
{
    loc.x = 0;
    loc.y = 0;

    prevLoc = loc;

    appearance = '-';
}
