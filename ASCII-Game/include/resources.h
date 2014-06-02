#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED

#include "windows.h"
#include "stdlib.h"
#include "time.h"

/*******************************
* Enum for distinguishing what
* type an object is.
* For collision detection.
*/
enum entity_type {
    ENTITY_TYPE_PLAYER = 0,
    ENTITY_TYPE_ENEMY,
    ENTITY_TYPE_BULLET
};

/*******************************
* Enum for distinguishing what
* type of collision occurred.
*/
enum collision_outcome_type {
    COLL_TYPE_NO_COLL = 0,
    COLL_TYPE_NOTHING,
    COLL_TYPE_DEAD
};

/*******************************
* Struct for the location of a
* game object.
* 2 params - x,y
*/
struct location {

    int x;
    int y;

};

/*******************************
* A struct for an individual
* score.
*/
struct Score {
  int     rankNum;
  char    initial [3];
  int     score;
};

/*******************************
* Function to clear the screen
* Obtained from cplusplus.com
*/
void ClearScreen();

/*******************************
* Function to generate a random
* number
*/
int RandomNumber(int minimum, int maximum);

#endif // RESOURCES_H_INCLUDED
