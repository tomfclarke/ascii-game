#include "../include/intromenu.h"

IntroMenu::IntroMenu()
{
    char tempIntroScreen[20][60] = {
    "###########################################################",
    "#                  --- OMEGA WARS ---                     #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "#                                                         #",
    "###########################################################"
    };

    for(int y = 0; y < 20; y++)
    {
        for(int x = 0; x < 60; x++)
        {
            introScreen[y][x] = tempIntroScreen[y][x];
        }
    }

    char tempIntroMsg[11][55] = {
    "It is the year 2142.                                  ",
    "   As the once hailed hero A.T.Symbol returns         ",
    "      from the planet Modulous of the Syntax System,  ",
    "         trouble ensues...                            ",
    "                                                      ",
    "Out of supplies, and fighting for life, Symbol is     ",
    "   intercepted by a swarm of Omega Fighters. With the ",
    "      ship hit and losing fuel,                       ",
    "                                                      ",
    "                       YOU                            ",
    "            Must take to the controls.                "
    };

    for(int y = 0; y < 11; y++)
    {
        for(int x = 0; x < 55; x++)
        {
            introMsg[y][x] = tempIntroMsg[y][x];
        }
    }

    char tempOptions[4][26] = {
    "        Play ..........  ",
    " High Scores ..........  ",
    "        Quit ..........  "
    };

    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 26; x++)
        {
            options[y][x] = tempOptions[y][x];
        }
    }

    char tempInstructions[6][26] = {
    "         CONTROLS        ",
    "                         ",
    "     Move   ->   D-Pad   ",
    "     Fire   ->   Space   ",
    "     Quit   ->   ESC     "
    };

    for(int y = 0; y < 6; y++)
    {
        for(int x = 0; x < 26; x++)
        {
            instructions[y][x] = tempInstructions[y][x];
        }
    }


    optionChosen = false;

    cursor.y = -1;
    cursor.x = 37;
}

void IntroMenu::displayIntroScreen()
{
    for(int y = 0; y < 20; y++)
    {
        for(int x = 0; x < 60; x++)
        {
            map[y][x] = introScreen[y][x];
        }
    }

    updateDisplay();

}

void IntroMenu::displayMessage()
{
    /// Run through dimensions of introMsg
        /// (minus endline char)
    for(int y = 0; y < 11; y++)
    {
        for(int x = 0; x < 54; x++)
        {
            /// Update the map
            map[3+y][4+x] = introMsg[y][x];

            updateDisplay();

            Sleep(5);

            if(GetAsyncKeyState(VK_ESCAPE))
            {
                return;
            }
        }

        Sleep(10);
    }

    Sleep(600);
}

int IntroMenu::displayOptions()
{
    /// Reset the cursor
    cursor.y = -1;

    /// Run through the dimensions of control menu
    for(int y = 0; y < 5; y++)
    {
        for(int x = 0; x < 25; x++)
        {
            /// Update the map with control menu
            map[6+y][15+x] = instructions[y][x];

        }
    }

    /// Run through the dimensions of options menu
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 25; x++)
        {
            /// Update the map with options menu
            map[15+y][13+x] = options[y][x];

            map[15+cursor.y][cursor.x] = '@';
        }
    }

    updateDisplay();

    Sleep(600);

    /// Reset chosen flag
    optionChosen = false;

    while(!optionChosen){ /// While an option hasnt been chosen

        Sleep(100);

        /// If down was pressed
        if(GetAsyncKeyState(VK_DOWN) && cursor.y < 2)
        {
            /// Clear the current position
            map[15+cursor.y][cursor.x] = ' ';
            /// Advance teh position
            cursor.y++;
            /// Set the new position
            map[15+cursor.y][cursor.x] = '@';

            updateDisplay();

            /// Play selection sound
            soundManager.playSound(SOUND_SELECT);

        }
        if(GetAsyncKeyState(VK_UP) && cursor.y > 0)
        {
            map[15+cursor.y][cursor.x] = ' ';

            cursor.y--;

            map[15+cursor.y][cursor.x] = '@';

            updateDisplay();

            /// Play selection sound
            soundManager.playSound(SOUND_SELECT);

        } /// If enter was pressed
        if(GetAsyncKeyState(VK_RETURN))
        {
            /// Play sound
            soundManager.playSound(SOUND_FIRE);

            /// Break out of the loop
            optionChosen = true;
        }
    }
    /// Return the selection
    return cursor.y;
}

