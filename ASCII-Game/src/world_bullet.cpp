#include "../include/world.h"

void World::fireBullet(Player* p)
{
    Bullet* b;

    /// Instantiate the bullet
    b = new Bullet;

    /// Temp location
    location bLoc;

    /// Store player location
    bLoc = p->getLocation();

    /// Advance the x position
    bLoc.x ++;

    /// Set the bullet location
    b->setLocation(bLoc);

    /// Draw the bullet on the map
    map[bLoc.y][bLoc.x] = b->getAppearance();

    /// Store the bullet in the bullet list
    bullet_list.push_back(b);

    /// Play 'bullet fired' sound
    soundManager.playSound(SOUND_FIRE);

}

bool World::updateBullet()
{
    /// Run through the vector of bullets
    for(int i = 0; i < (int)bullet_list.size(); i++)
    {
        /// Temp location
        location newLoc;

        /// Get the current location
        newLoc = bullet_list[i]->getLocation();

        /// Advance the proposed location
        newLoc.x ++;

        /// Set the location
        bullet_list[i]->setLocation(newLoc);
    }

    /// If the vector is not empty return true
    if(bullet_list.size() > 0)
    {
        return true;
    }

    return false;
}
