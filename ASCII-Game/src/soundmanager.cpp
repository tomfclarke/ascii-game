#include "../include/soundmanager.h"

SoundFXManager::SoundFXManager()
{

}

bool SoundFXManager::loadSounds()
{
    /// Load each sound into buffer array

    if(!buffer[SOUND_BEGIN].loadFromFile("./sounds/sound_begin.wav"))
    {
        cout << "Unable to load sound: sound_begin.wav \n";

        return false;
    }

    if(!buffer[SOUND_FIRE].loadFromFile("./sounds/sound_fire.wav"))
    {
        cout << "Unable to load sound: sound_fire.wav \n";

        return false;
    }

    if(!buffer[SOUND_LOSELIFE].loadFromFile("./sounds/sound_loselife.wav"))
    {
        cout << "Unable to load sound: sound_loselife.wav \n";

        return false;
    }

    if(!buffer[SOUND_ENEMYDEAD].loadFromFile("./sounds/sound_enemydead.wav"))
    {
        cout << "Unable to load sound: sound_enemydead.wav \n";

        return false;
    }

    if(!buffer[SOUND_SELECT].loadFromFile("./sounds/sound_select.wav"))
    {
        cout << "Unable to load sound: sound_select.wav \n";

        return false;
    }

    if(!buffer[SOUND_ENDGAME].loadFromFile("./sounds/sound_endgame.wav"))
    {
        cout << "Unable to load sound: sound_endgame.wav \n";

        return false;
    }

    if(!introMusic.openFromFile("./sounds/intro_music.wav"))
    {
        cout << "Unable to load intro music... \n";

        return false;
    }

    if(!gameMusic.openFromFile("./sounds/game_music.wav"))
    {
        cout << "Unable to load intro music... \n";

        return false;
    }

    introMusic.setLoop(true);
    gameMusic.setLoop(true);
    introMusic.setVolume(50);
    gameMusic.setVolume(50);

    return true;
}

void SoundFXManager::playSound(int soundID)
{
    /// Set the correct buffer to use
    sound.setBuffer(buffer[soundID]);

    /// Play the sound
    sound.play();
}

void SoundFXManager::playMusic(int musicID)
{
    /// Stop music that is already playing
    introMusic.stop();
    gameMusic.stop();

    /// ID selects correct sound to play
    switch(musicID)
    {
        /// For each, set loop to true then play
        case 0:
                introMusic.play(); break;
        case 1:
                gameMusic.play(); break;
    }
}

void SoundFXManager::stopMusic()
{
    introMusic.stop();
    gameMusic.stop();

}
