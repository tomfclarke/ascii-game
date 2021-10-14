#include <iostream>

#include "include/world.h"
#include "include/intromenu.h"

using namespace std;

/*********************************************************
*                   MAIN FUNCTION
*
*
***** TODO:
** -------- Create 'level' system from spawn speeds
** -------- Create introduction message
** -------- Beat James' high score...
*/

int main()
{
    /*******************************
    * Some variables for main
    */
    char direction = NULL;

    bool game_running = false;
    bool play_again   = true;
    bool first_play   = true;
    bool refreshPlayer = true;
    bool refreshEnemy  = false;
    bool refreshBullet = false;

    int loopCounter = 0;
    int bulletRate = 0;
    int spawnRate = 0;

    int selector = -1;


    /// Create an intro instance
    IntroMenu title;

    /// Create world instance
    World* lvl1;

    /// Create a Player instance
    Player* plyr1;

while(play_again == true)
{
    lvl1 = new World;

    plyr1 = new Player;

    lvl1->playMusic(0);

    /// Display the title screen
    title.displayIntroScreen();

    if(first_play)
    {
        /// Display the introduction message
        title.displayMessage();

        first_play = false;
    }

    while(game_running == false)
    {
        title.displayIntroScreen();

        selector = title.displayOptions();

        if(selector == 0)
        {
            game_running = true;

            break;
        }
        else if(selector == 1)
        {
            lvl1->showHighScores();
        }
        else if(selector == 2)
        {
            return 0;
        }
    }

    /// Update the map
    lvl1->updateMap(plyr1);

    /// Show the display
    lvl1->updateDisplay();

    /// Play music
    lvl1->playMusic(1);

    while(game_running == true)     ///Start of game loop
    {
        /// Increment the loop counter
        loopCounter++;

        /// Reset direction
        direction = NULL;


        /*************************************
        *       NORMAL DIRECTIONS
        */
        if(GetAsyncKeyState(VK_DOWN))   ///Arrow key down
        {
            direction = 'd';
            refreshPlayer = true;
        }
        if(GetAsyncKeyState(VK_UP))     ///Arrow key up
        {
            direction = 'u';
            refreshPlayer = true;
        }
        if(GetAsyncKeyState(VK_RIGHT))  ///Arrow key right
        {
            direction = 'r';
            refreshPlayer = true;
        }
        if(GetAsyncKeyState(VK_LEFT))   ///Arrow key left
        {
            direction = 'l';
            refreshPlayer = true;
        }
        /*************************************
        *       DIAGONAL DIRECTIONS
        */
        if(GetAsyncKeyState(VK_UP)&&GetAsyncKeyState(VK_LEFT))   ///Arrow key up/left
        {
            direction = 'q';
            refreshPlayer = true;
        }
         if(GetAsyncKeyState(VK_UP)&&GetAsyncKeyState(VK_RIGHT))   ///Arrow key up/right
        {
            direction = 'e';
            refreshPlayer = true;
        }
        if(GetAsyncKeyState(VK_DOWN)&&GetAsyncKeyState(VK_RIGHT))   ///Arrow key down/right
        {
            direction = 'c';
            refreshPlayer = true;
        }
        if(GetAsyncKeyState(VK_DOWN)&&GetAsyncKeyState(VK_LEFT))   ///Arrow key down/left
        {
            direction = 'z';
            refreshPlayer = true;
        }
        /*************************************
        *       FIRE BULLET
        */
        bulletRate++;

        if(GetAsyncKeyState(VK_SPACE) && bulletRate > 5)
        {
            /// Fire a bullet giving the address of plyr1
            /// to get their location
            lvl1->fireBullet(plyr1);

            bulletRate = 0;

        }

        /*******************************************
        *       UPDATE OBJECTS, MAP AND DISPLAY
        */

        /// Check the score
        /// This adjusts the spawn rate too
        lvl1->checkScore();

        /// Set spawn rate
        spawnRate = lvl1->getSpawnRate();
        /// SPAWN ENEMY
        /// If the counter is over the spawn rate
        if (loopCounter > spawnRate)
        {
            /// Spawn an ememy
            lvl1->spawnEnemy();

            /// Reset the loop counter
            loopCounter = 0;
        }

        /// UPDATE ENEMY
        /// Update any enemy's position setting refresh
        /// to true if enemies are present
        refreshEnemy = lvl1->updateEnemy();

        /// FIRE BULLETS
        /// Update position of bullets setting refresh
        /// to true if bullets are there
        refreshBullet = lvl1->updateBullet();

        /// Direction
        /// If a direction has been pressed
        /// or a bullet has been fired or enemies are present
        if (refreshEnemy == true || refreshBullet == true
            || refreshPlayer == true)
        {
            /// If player has moved
            if (refreshPlayer == true){
                /// Move player
                lvl1->movePlayer(direction, plyr1);
            }

            /// Check collisions
            lvl1->checkCollisions(plyr1);

            /// Update map
            lvl1->updateMap(plyr1);

            /// Update lives
            lvl1->showPlayerLives(plyr1);

            /// Update display
            lvl1->updateDisplay();

            /// Reset player refresh
            refreshPlayer = false;
        }

        game_running = lvl1->checkPlayerLives(plyr1);

        /// Wait 30 milliseconds
        Sleep(60);

        /*************************************
        *       QUIT
        */
        if(GetAsyncKeyState(VK_ESCAPE)) ///Escape to exit
        {
            game_running = false;       ///set bool to false to break out of game loop
        }

    }/// End of game loop

    /// Display end game message...
        /// Add score to highscores
    lvl1->updateHighScores(plyr1);

    /// Show highscores
    lvl1->showHighScores();

    /// Ask user to play again

    Sleep(50);

    if(lvl1->playAgain() == false)
    {
        play_again = false;
    }

    delete lvl1;

    delete plyr1;

}/// End of play again loop

    return 0;
}


