#ifndef PLAYER_H
#define PLAYER_H

#include "C:/Users/Clarke/Documents/Codeblocks/OOmapGame/resources.h"

class Player
{
    private:
        location loc, prevLoc;
        char appearance;

        int lives;

    public:
        Player();

        location getLocation() {return loc;}
        location getPrevLocation() {return prevLoc;}

        int getLives() {return lives;}
        void decrementLives() {lives--;}

        char getAppearance() {return appearance;}

        void setLocation(location newLoc, bool setPrev)
                { if(setPrev){prevLoc = loc;}
                    loc.x = newLoc.x; loc.y = newLoc.y;}

        void resetLocation() {loc.x = 2; loc.y = 5;}

};

#endif // PLAYER_H
