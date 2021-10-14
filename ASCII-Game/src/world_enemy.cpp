#include "../include/world.h"

void World::spawnEnemy()
{
    Enemy* e;

    /// Instantiate the enemy
    e = new Enemy;

    /// Temp location
    location eLoc;

    /// Set the x coordinate to beside the
    /// right wall
    eLoc.x = 57;

    /// Set the y coordinate to a
    /// random number between the top and
    /// bottom walls.
    int randomY;
    randomY = RandomNumber(6,11);

    /// Extra range check to cut out bad access errors
        /// While random number is NOT in range
    while(randomY < 6 || randomY > 18)
    {
        /// Request another random number
        randomY = RandomNumber(6,11);
    }

    /// Set the number to the y coordinate
    eLoc.y = randomY;


    /// Set the enemy location
    e->setLocation(eLoc);

    /// Draw the enemy on the map
    map[eLoc.y][eLoc.x] = e->getAppearance();

    /// Store the enemy in the enemy list
    enemy_list.push_back(e);

}

bool World::updateEnemy()
{
    /// Run through vector of enemies
    for(int i = 0; i < enemy_list.size(); i++)
    {
        /// Temp location
        location newLoc;

        /// Get the current location
        newLoc = enemy_list[i]->getLocation();

        /// Advance the proposed location
        newLoc.x --;

        /// Set the location
        enemy_list[i]->setLocation(newLoc);
    }

    /// If vector is not empty return true
    if(enemy_list.size() > 0)
    {
        return true;
    }

    return false;
}
