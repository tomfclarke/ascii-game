#ifndef BULLET_H
#define BULLET_H

#include "C:/Users/Clarke/Documents/Codeblocks/OOmapGame/resources.h"

class Bullet
{
    private:
        location loc, prevLoc;
        char appearance;

    public:
        Bullet();

        location getLocation() {return loc;}
        location getPrevLocation() {return prevLoc;}

        char getAppearance() {return appearance;}

        void setLocation(location newLoc)
                {prevLoc = loc; loc.x = newLoc.x; loc.y = newLoc.y;}
};

#endif // BULLET_H
