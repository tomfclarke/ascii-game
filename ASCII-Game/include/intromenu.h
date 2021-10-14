#ifndef INTROMENU_H
#define INTROMENU_H

#include "world.h"

class IntroMenu : public World
{
private:

    char introScreen[20][60];

    char introMsg[11][55];

    char options[4][26];

    char instructions[6][26];

    location cursor;

    bool optionChosen;

public:

    IntroMenu();

    void displayIntroScreen();

    void displayMessage();

    int displayOptions();

};

#endif // INTROMENU_H
