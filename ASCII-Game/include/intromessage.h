#ifndef INTROMESSAGE_H
#define INTROMESSAGE_H

#include "resources.h"

class intromessage
{
    private:

        char map [20][60];

        int msglength;

        location CharLoc;

    public:

        intromessage();

        int getLength() { return msglength; }

        void showChar(int CharNum);


};

#endif // INTROMESSAGE_H
