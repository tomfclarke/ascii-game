#ifndef ENEMY_H
#define ENEMY_H

#include "C:/Users/Clarke/Documents/Codeblocks/OOmapGame/resources.h"

class Enemy
{
    private:
        location loc, prevLoc;
        char appearance;

    public:
        Enemy();

        char getAppearance() {return appearance;}

        location getLocation() {return loc;}
        location getPrevLocation() {return prevLoc;}

        void setLocation(location newLoc)
                    {prevLoc = loc; loc.x = newLoc.x; loc.y = newLoc.y;}

};

#endif // ENEMY_H
