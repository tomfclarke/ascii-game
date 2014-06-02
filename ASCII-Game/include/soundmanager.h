#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;

enum {
    SOUND_BEGIN = 0,
    SOUND_FIRE,
    SOUND_LOSELIFE,
    SOUND_ENEMYDEAD,
    SOUND_SELECT,
    SOUND_ENDGAME
};


class SoundFXManager
{
private:

    sf::SoundBuffer buffer[6];

    sf::Sound sound;

    sf::Music introMusic;
    sf::Music gameMusic;

public:

    SoundFXManager();

    bool loadSounds();

    void playSound(int soundID);

    void playMusic(int musicID);

    void stopMusic();

};

#endif // SOUNDMANAGER_H
