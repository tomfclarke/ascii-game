#include "../include/player.h"

Player::Player()
{
    loc.x = 2;
    loc.y = 5;

    prevLoc = loc;

    appearance = '@';

    lives = 5;
}
