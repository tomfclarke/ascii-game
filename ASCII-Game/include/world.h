#ifndef WORLD_H
#define WORLD_H

#define _WIN32_WINNT 0x0600

#include <iostream>
#include <vector>
#include <sstream>
#include "stdio.h"
#include "time.h"

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "scoring.h"
#include "soundmanager.h"

using namespace std;

class World
{
    private:

        vector <Bullet*> bullet_list;
        vector <Enemy*>  enemy_list;

        bool refresh;

        Scoring scoreSystem;

        unsigned int spawnRate;

        int level;

    protected:

        char map [20][60];

        SoundFXManager soundManager;

    public:

        World();

        void movePlayer(char direction, Player* p);

        void fireBullet(Player* p);
        bool updateBullet();

        void spawnEnemy();
        bool updateEnemy();
        unsigned int getEnemyListSize() {return enemy_list.size();}

        unsigned int getSpawnRate() {return spawnRate;}

        bool getRefresh() {return refresh;}


        void updateScore(int addToScore);
        void checkScore();

        void updateHighScores(Player* p);
        void showHighScores();

        void showPlayerLives(Player* p);
        bool checkPlayerLives(Player* p);

        void checkCollisions(Player* p);

        void updateMap(Player* p);

        void updateDisplay();

        bool playAgain();

        void playMusic(int tuneID) {soundManager.playMusic(tuneID);}


        ~World();

};

#endif // WORLD_H
