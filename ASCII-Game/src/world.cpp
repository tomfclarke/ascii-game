#include "C:/Users/Clarke/Documents/Codeblocks/OOmapGame/include/world.h"

using namespace std;

World::World()
{
    char tempMap[20][60] = {
    "###########################################################",
    "#                  --- OMEGA WARS ---                     #",
    "#  Lives:               Level 1            Score:   0000  #",
    "###########################################################",
    "#                                                         #",
    "# @                                                       #",
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
    "###########################################################",
    };

    for(int y = 0; y < 20; y++)
    {
        for(int x = 0; x < 60; x++)
        {
            map[y][x] = tempMap[y][x];
        }
    }

    refresh = false;

    level = 1;

    spawnRate = 20;

    bullet_list.clear();
    enemy_list.clear();

    if(!soundManager.loadSounds())
    {
        cin.get();
    }

    /// Load highscores from file
    if(!scoreSystem.loadHighScores())
    {
        /// If not loaded, file does not exist
        /// so save scores...
        if(!scoreSystem.saveHighScores())
        {
            /// If unable to save, there is a
            /// problem with the file
            cout << "Load failed... \n";

            cin.get();

            return;
        }
    }
}

void World::movePlayer(char direction, Player* p)
{
    /// Temp location
    location newLoc;

    /// Get the current location
    newLoc = p->getLocation();

    /// Determine direction of travel and
    /// adjust the new postion accordingly
    switch(direction)
    {
        case 'u': newLoc.y --; break;
        case 'd': newLoc.y ++; break;
        case 'l': newLoc.x --; break;
        case 'r': newLoc.x ++; break;
        case 'q': newLoc.y --; newLoc.x --; break;
        case 'e': newLoc.y --; newLoc.x ++; break;
        case 'c': newLoc.x ++; newLoc.y ++; break;
        case 'z': newLoc.x --; newLoc.y ++; break;
        default: break;
    }

    /// Update the position of player
    p->setLocation(newLoc,true);

}

/// ----------------------  This is where collision check starts

void World::checkCollisions(Player* p)
{
    /// Temporary locations
    location pLoc = p->getLocation();
    location eLoc, bLoc;

/// Check player location against walls
        /// If player = wall...
    if(map[pLoc.y][pLoc.x] == '#')
    {
        /// Set players location to previous loc
        p->setLocation(p->getPrevLocation(),false);
    }

    /// Run through enemy list
    for(int i = 0; i < enemy_list.size(); i++)
    {
        /// Store enemy location in temp loc
        eLoc = enemy_list[i]->getLocation();

/// Check enemy locations against player
        /// If enemy loc = player loc...
        if((eLoc.y == pLoc.y && eLoc.x == pLoc.x)
            ||(eLoc.y == pLoc.y && eLoc.x == pLoc.x+1))
        {
            /// Reset player loc
            p->resetLocation();

            /// Decrease lives by 1
            p->decrementLives();

            /// Play 'lifelost' sound
            soundManager.playSound(SOUND_LOSELIFE);

        }

/// Check enemy locations against walls
            /// If enemy = wall...
        if(map[eLoc.y][eLoc.x] == '#')
        {
            /// Store the previous location
            location ePrev = enemy_list[i]->getPrevLocation();

            /// Clear the previous location
            map[ePrev.y][ePrev.x] = ' ';

            /// Delete enemy
            delete enemy_list[i];

            /// Erase entry from the vector list
            enemy_list.erase(enemy_list.begin() + i);

            /// Update score
            updateScore(-5);
        }
    }

    /// Run through bullet list
    for(int ib = 0; ib < bullet_list.size(); ib++)
    {
        /// Store bullet location in temp loc
        bLoc = bullet_list[ib]->getLocation();

/// Check player location against bullets
            /// If player = bullet...
        if(bLoc.y == pLoc.y && bLoc.x == pLoc.x)
        {
            /// Store the previous location
            location bPrev = bullet_list[ib]->getPrevLocation();

            /// Clear the previous location
            map[bPrev.y][bPrev.x] = ' ';

            /// Delete bullet
            delete bullet_list[ib];

            /// Remove entry from vector list
            bullet_list.erase(bullet_list.begin() + ib);
        }

        /// Run through enemy list again for each bullet
            /// ... (very inefficient)
        for(int ie = 0; ie < enemy_list.size(); ie++)
        {
            /// Store enemy location in temp loc
            eLoc = enemy_list[ie]->getLocation();

/// Check bullet locations against enemies
                /// If bullet = enemy...
            if((bLoc.y == eLoc.y && bLoc.x == eLoc.x)
               ||(bLoc.y == (eLoc.y) && bLoc.x == (eLoc.x-1)))
            {
                /// Store the previous location
                location ePrev = enemy_list[ie]->getPrevLocation();

                /// Clear the previous location
                map[ePrev.y][ePrev.x] = ' ';

                /// Delete enemy
                delete enemy_list[ie];

                /// Remove entry from vector list
                enemy_list.erase(enemy_list.begin() + ie);

                /// Update score
                updateScore(10);

                /// Store the previous location
                location bPrev = bullet_list[ib]->getPrevLocation();

                /// Clear the previous location
                map[bPrev.y][bPrev.x] = ' ';

                /// Delete bullet
                delete bullet_list[ib];

                /// Remove entry from vector list
                bullet_list.erase(bullet_list.begin() + ib);

                /// Play sound
                soundManager.playSound(SOUND_ENEMYDEAD);
            }
        }

/// Check bullet locations against walls
            /// If bullet = wall...
        if(map[bLoc.y][bLoc.x] == '#')
        {
            /// Store the previous location
            location bPrev = bullet_list[ib]->getPrevLocation();

            /// Clear the previous location
            map[bPrev.y][bPrev.x] = ' ';

            /// Delete bullet
            delete bullet_list[ib];

            /// Remove entry from vector list
            bullet_list.erase(bullet_list.begin() + ib);
        }
    }
}

/// ------------------------------------- End of collision checks

void World::updateMap(Player* p)
{
    /// Store players locations
    location pLoc = p->getLocation();
    location pPrev = p->getPrevLocation();
    /// Draw player on map and clear previous location
    map[pPrev.y][pPrev.x] = ' ';
    map[pLoc.y][pLoc.x] = p->getAppearance();

    for(int i = 0; i < bullet_list.size(); i++)
    {
        /// Store bullet location
        location bLoc = bullet_list[i]->getLocation();
        location bPrev = bullet_list[i]->getPrevLocation();
        /// Draw bullet on map and clear previous location
        map[bLoc.y][bLoc.x] = bullet_list[i]->getAppearance();
        map[bPrev.y][bPrev.x] = ' ';
    }

    for(int i = 0; i < enemy_list.size(); i++)
    {
        /// Store enemy location
        location eLoc = enemy_list[i]->getLocation();
        location ePrev = enemy_list[i]->getPrevLocation();
        /// Draw enemy on map and clear previous location
        map[eLoc.y][eLoc.x] = enemy_list[i]->getAppearance();
        map[ePrev.y][ePrev.x] = ' ';
    }
}

void World::updateDisplay()
{
    LockWindowUpdate(GetConsoleWindow());

    ClearScreen();

    for(int numLines = 0; numLines < 20; numLines++)
    {
        cout << map[numLines] << endl;
    }

    LockWindowUpdate(NULL);
}

void World::updateScore(int addToScore)
{
    /// Temp score
    int score;

    /// Get the current score
    score = scoreSystem.getCurrentScore();

    /// Add the points to the score
    score += addToScore;

    /// Set the new score
    scoreSystem.setCurrentScore(score);

    /// Temp char array to hold text score
    char txtScore[5];

    /// Print score from scoring system into array
    sprintf(txtScore, "%04d #", scoreSystem.getCurrentScore());

    /// Update score on map
    for(int i = 0; i < 5; i++)
    {
        map[2][52+i] = txtScore[i];
    }
}

void World::checkScore()
{
    int score = scoreSystem.getCurrentScore();


    if(score >100 && score <200 && level <= 1){
        spawnRate = 16;
        level = 2;
        map[2][30] = '2';
    }else if(score >200 && score <300 && level <=2){
        spawnRate = 12;
        level = 3;
        map[2][30] = '3';
    }else if(score >300 && score <400 && level <=3){
        spawnRate = 10;
        level = 4;
        map[2][30] = '4';
    }else if(score >400 && score <500 && level <=4){
        spawnRate = 8;
        level = 5;
        map[2][30] = '5';
    }else if(score >500 && score <600 && level <=5){
        spawnRate = 7;
        level = 6;
        map[2][30] = '6';
    }else if(score >600 && score <700 && level <=6){
        spawnRate = 6;
        level = 7;
        map[2][30] = '7';
    }else if(score >700 && score <800 && level <=7){
        spawnRate = 5;
        level = 8;
        map[2][30] = '8';
    }else if(score >800 && score <900 && level <=8){
        spawnRate = 4;
        level = 9;
        map[2][30] = '9';
    }else if(score >900 && score <1000 && level <=9){
        spawnRate = 3;
        level = 10;
        map[2][30] = '1';
        map[2][31] = '0';
    }else if(score >1000 && score <1200 && level <=10){
        spawnRate = 2;
        level = 11;
        map[2][31] = '1';
    }else if(score >1200 && score <1400 && level <=11){
        spawnRate = 2;
        level = 12;
        map[2][31] = '2';
    }else if(score >1400 && level <=12){
        spawnRate = 1;
        level = 13;
        map[2][31] = '3';
    }else{
        spawnRate = 20;
    }
}

void World::showPlayerLives(Player* p)
{
    /// Get the lives
    int lives = p->getLives();

    /// Clear previous lives on map
    for(int i = 0; i < 5; i++)
    {
        map[2][10+i] = ' ';
    }

    /// Print lives on map
    for(int i = 0; i < lives; i++)
    {
        map[2][10+i] = 157;
    }

}

bool World::checkPlayerLives(Player* p)
{
    /// Get lives
    int lives = p->getLives();

    /// If no lives are left
    if(lives <= 0)
    {
        /// Stop music
        soundManager.stopMusic();

        /// Play 'end game' sound
        soundManager.playSound(SOUND_ENDGAME);

        return false;
    }

    /// Otherwise...
    return true;
}

void World::updateHighScores(Player* p)
{
    /// Temp initials and score
    char initial[4];
    int  score;
    Score lowestHighScore;

    /// Store the players current score
    score = scoreSystem.getCurrentScore();

    /// Store rank 10's score
    lowestHighScore = scoreSystem.getHScore(9);

    /// Check if the high score has been beaten
    if(score < lowestHighScore.score)
    {
        /// Not beaten, exit function
        return;
    }

    /// Message "window" in char array
    char scoreMsg[5][30] = {
    "#############################",
    "#      New High Score!!     #",
    "#  Please enter initials... #",
    "#############################",
    };

    /// Run through array
        /// Loop stops before end line char to
        /// preserve map edges.
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 29; x++)
        {
            map[8+y][15+x] = scoreMsg[y][x];

        }
    }
    updateDisplay();

    GetAsyncKeyState(VK_RETURN);
    cout << "Press the enter key... \n";
    while(!GetAsyncKeyState(VK_RETURN))
    {
        Sleep(60);
    }

    cout << "Please enter first initial: ";
    cin  >> &initial[0];

    cout << "Please enter second initial: ";
    cin  >> &initial[1];

    cout << "Please enter third initial: ";
    cin  >> &initial[2];

    /// Put the score in the high scores
    scoreSystem.setHScore(initial[0],initial[1],initial[2],score);

    /// Save highscores
    if(!scoreSystem.saveHighScores())
    {
        cout << "Save failed... \n";

        Sleep(600);

        return;
    }

    GetAsyncKeyState(VK_RETURN);

}

void World::showHighScores()
{
    /// Temporary high score table
    char highScoreTable[15][30] = {
    "#############################",
    "#        High Scores        #",
    "#                           #",
    "#     1.     ......         #",
    "#     2.     ......         #",
    "#     3.     ......         #",
    "#     4.     ......         #",
    "#     5.     ......         #",
    "#     6.     ......         #",
    "#     7.     ......         #",
    "#     8.     ......         #",
    "#     9.     ......         #",
    "#    10.     ......         #",
    "#############################"
    };

    /// Fills table with high scores from scoreSystem
    for(int i = 3; i < 13; i++)
    {
        Score tempScore = scoreSystem.getHScore(i-3);

        highScoreTable[i][8] = tempScore.initial[0];
        highScoreTable[i][9] = tempScore.initial[1];
        highScoreTable[i][10] = tempScore.initial[2];

        char textScore[5];
        sprintf(textScore, "%04d  #", tempScore.score);

        for(int j = 0; j < 4; j++)
        {
            highScoreTable[i][22+j] = textScore[j];
        }
    }

    /// Fills map with whole high score table
    for(int y = 0; y < 14; y++)
    {
        for(int x = 0; x < 29; x++)
        {
            map[5+y][15+x] = highScoreTable[y][x];
        }
    }

    updateDisplay();

    cout << "Please press enter to continue... \n";

    Sleep(600);

    while(!GetAsyncKeyState(VK_RETURN))
    {
        Sleep(60);

    }

    /// Clear the highscores from the map
    for(int y = 0; y < 14; y++)
    {
        for(int x = 0; x < 29; x++)
        {
            map[5+y][15+x] = ' ';
        }
    }
}

bool World::playAgain()
{
    /// Message "window" in char array
    char scoreMsg[5][30] = {
    "#############################",
    "#      Ship Destroyed.      #",
    "# Would you like another go?#",
    "#############################",
    };

    /// Run through array
        /// Loop stops before end line char to
        /// preserve map edges.
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 29; x++)
        {
            map[8+y][15+x] = scoreMsg[y][x];

        }
    }
    updateDisplay();

    char temp = '0';

    cout << "Please enter Y or N: ";
    cin >> temp;

    while(true)
    {
        if(temp == 'n' || temp == 'N')
        {
            return false;
        }

        if(temp == 'y' || temp == 'Y')
        {
            return true;

        }else {

            cout << "\nBad entry, please enter Y or N: ";
            cin >> temp;
        }
    }
}

World::~World()
{
    bullet_list.clear();

    enemy_list.clear();

}
