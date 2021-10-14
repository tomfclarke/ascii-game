#ifndef SCORING_H
#define SCORING_H

#include <iostream>
#include <fstream>

#include "resources.h"

///
/// The scoring class
///
class Scoring
{
private:

    int currentScore;

    /// The highScore array of Score structs
    Score highScore [10];

    std::ifstream hSFileIn;
    std::ofstream hSFileOut;

public:

    Scoring();

    bool setHScore(char firstI, char secondI, char thirdI, int newScore);
    Score getHScore(int rankNum) { return highScore[rankNum]; }

    void setCurrentScore(int newScore);
    int  getCurrentScore()  { return currentScore; }

    bool saveHighScores();
    bool loadHighScores();
};

#endif // SCORING_H
