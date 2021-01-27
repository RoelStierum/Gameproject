#include "SoundManager.hpp"
#include "DEFINITIONS.hpp"

namespace engine{
	//Class to manage all the ingame soundeffects and background music.
	SoundManager::SoundManager() {
		CheckSoundLoading();
		SetSoundBuffers();
		setVolume();
        BackGroundMusic.setLoop(true);
	}

	//Check if the sounds and music are loaded. Send an error message if a sound effect or the music isn't loaded.
	void SoundManager::CheckSoundLoading(){
		if ( !_jumpSoundBuffer.loadFromFile(JUMP_SOUND_FILEPATH) ){
			std::cout << "Error loading jump sound effect\n";
		}if ( !_deathSoundBuffer.loadFromFile(DEATH_SOUND_FILEPATH) ){
            std::cout << "Error loading death sound effect\n";
        }if ( !_powerupSoundBuffer.loadFromFile(POWERUP_SOUND_FILEPATH) ){
            std::cout << "Error loading powerup sound effect\n";
        }if ( !_clickButtonSoundBuffer.loadFromFile(CLICK_SOUND_FILEPATH) ){
            std::cout << "Error loading click sound effect\n";
        }if ( !_flagSoundBuffer.loadFromFile(WIN_SOUND_FILEPATH) ){
            std::cout << "Error loading click sound effect\n";
        }if(!BackGroundMusic.openFromFile(MUSIC_FILEPATH)){
            std::cout << "Error loading music\n";
		}
	}

	//Set buffers for the soundeffects.
	void SoundManager::SetSoundBuffers(){
		_jumpSound.setBuffer( _jumpSoundBuffer );
		_deathSound.setBuffer(_deathSoundBuffer);
		_powerupSound.setBuffer(_powerupSoundBuffer);
		_clickButtonSound.setBuffer(_clickButtonSoundBuffer);
		_flagSound.setBuffer(_flagSoundBuffer);
	}

	//Set the volume of the sound effects and the music so that they won't be to loud.
	void SoundManager::setVolume() {
        _jumpSound.setVolume(JUMP_SOUND_VOLUME);
        _clickButtonSound.setVolume(CLICK_SOUND_VOLUME);
        _deathSound.setVolume(DEATH_SOUND_VOLUME);
        _flagSound.setVolume(WIN_SOUND_VOLUME);
        _powerupSound.setVolume(POWERUP_SOUND_VOLUME);
        BackGroundMusic.setVolume(MUSIC_VOLUME);
	}

	//Set the volume of all soundeffects and music to zero so that they will be muted.
	//This can be used with the mute button in the main menu.
    void SoundManager::mute() {
        _jumpSound.setVolume(0);
        _clickButtonSound.setVolume(0);
        _deathSound.setVolume(0);
        _flagSound.setVolume(0);
        _powerupSound.setVolume(0);
        BackGroundMusic.setVolume(0);
    }

}