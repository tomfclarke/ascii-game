#include "C:/Users/Clarke/Documents/Codeblocks/OOmapGame/include/scoring.h"

Scoring::Scoring()
{
    /// Run through high score array and set defaults
    for(int i=0; i < 10; i++)
    {
        /// Set the rank of each the entry
        highScore[i].rankNum = i+1;

        /// Set all the initials to '-'
        for(int c=0; c < 3; c++)
        {
            highScore[i].initial[c] = '-';
        }

        /// Set the score to 0000
        highScore[i].score = 0000;

    }

    currentScore = 0000;
}

bool Scoring::setHScore(char firstI, char secondI, char thirdI, int newScore)
{
    int currScore = 0;

    int newRank = 0;

    /// Compare score to other scores in high score list
    for (int i=0; i < 10; i++)
    {
        currScore = highScore[i].score;

        if (newScore > currScore)
        {
            /// Set the new rank position
            newRank = i;

            /// Move all scores down below new rank
            for (int y=9; y > newRank; y--)
            {
                highScore[y] = highScore[y-1];
            }

            /// Fill in new rank details
            highScore[newRank].score = newScore;
            highScore[newRank].initial[0] = firstI;
            highScore[newRank].initial[1] = secondI;
            highScore[newRank].initial[2] = thirdI;

            /// Return true to indicate scores have been updated
            return true;
        }
    }
    /// If nothing has been updated...
    return false;
}

void Scoring::setCurrentScore(int newScore)
{
    if(newScore > 0)
    {
        currentScore = newScore;
    }else{
        currentScore = 0;
    }
}

bool Scoring::saveHighScores()
{
    /// Open the highscores file.
        /// If non existant, a new file will be created
    hSFileOut.open("C:/Users/Clarke/Documents/Codeblocks/OOmapGame/highscores.txt");

    /// Check if the file is open
    if(hSFileOut.is_open())
    {
        /// Run through the high score list
        for(int i = 0; i < 10; i++)
        {
            /// Write from highscore entry into file
                /// Separate intials and score by a space
            hSFileOut << highScore[i].initial[0];
            hSFileOut << highScore[i].initial[1];
            hSFileOut << highScore[i].initial[2] << " ";

            hSFileOut << highScore[i].score;

            hSFileOut << "\n"; /// End the line
        }

        /// Close file
        hSFileOut.close();

        return true;

    }else{

        /// Indicate a failed attempt
        return false;
    }
}

bool Scoring::loadHighScores()
{
    /// Open the highscores file
    hSFileIn.open("C:/Users/Clarke/Documents/Codeblocks/OOmapGame/highscores.txt");

    /// Temp initials and score
    char hsInit[3];
    int hsScore = 0;

    /// Check if the file has opened
    if(hSFileIn.is_open())
    {
        /// Run through high score array
        for(int i = 0; i < 10; i++)
        {
            /// Read from file into temp char array
            hSFileIn >> hsInit[0] >> hsInit[1] >> hsInit[2];

            /// Read from file into temp score
            hSFileIn >> hsScore;

            /// Copy the temp values into highscore entry
            highScore[i].initial[0] = hsInit[0];
            highScore[i].initial[1] = hsInit[1];
            highScore[i].initial[2] = hsInit[2];
            highScore[i].score = hsScore;
        }

        /// Close the file
        hSFileIn.close();

        return true;

    }else{

        /// Indicate a failed attempt
        return false;
    }

}
