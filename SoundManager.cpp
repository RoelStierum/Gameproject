#include "SoundManager.hpp"
#include "DEFINITIONS.hpp"

namespace engine{

	SoundManager::SoundManager() {
		CheckSoundLoading();
		SetSoundBuffers();
		setVolume();
        BackGroundMusic.setLoop(true);
	}

	void SoundManager::CheckSoundLoading(){
		if ( !_jumpSoundBuffer.loadFromFile(JUMP_SOUND_FILEPATH) ){
			std::cout << "Error loading wing sound effect\n";
		}if ( !_deathSoundBuffer.loadFromFile(DEATH_SOUND_FILEPATH) ){
            std::cout << "Error loading death sound effect\n";
        }if ( !_coinSoundBuffer.loadFromFile(POWERUP_SOUND_FILEPATH) ){
            std::cout << "Error loading coin sound effect\n";
        }

        if ( !_clickSoundBuffer.loadFromFile(CLICK_SOUND_FILEPATH) ){
            std::cout << "Error loading click sound effect\n";
        }
        if ( !_winSoundBuffer.loadFromFile(WIN_SOUND_FILEPATH) ){
            std::cout << "Error loading click sound effect\n";
        }

		if(!BackGroundMusic.openFromFile(MUSIC_FILEPATH)){
            std::cout << "Error loading music\n";
		}
	}

	void SoundManager::SetSoundBuffers(){
		_jumpSound.setBuffer( _jumpSoundBuffer );
		_deathSound.setBuffer(_deathSoundBuffer);
		_coinSound.setBuffer(_coinSoundBuffer);
		_clickSound.setBuffer(_clickSoundBuffer);
		_winSound.setBuffer(_winSoundBuffer);
	}

	void SoundManager::setVolume() {
        _jumpSound.setVolume(JUMP_SOUND_VOLUME);
        _clickSound.setVolume(CLICK_SOUND_VOLUME);
        _deathSound.setVolume(DEATH_SOUND_VOLUME);
        _winSound.setVolume(WIN_SOUND_VOLUME);
        _coinSound.setVolume(POWERUP_SOUND_VOLUME);
        BackGroundMusic.setVolume(MUSIC_VOLUME);
	}

    void SoundManager::mute() {
        _jumpSound.setVolume(0);
        _clickSound.setVolume(0);
        _deathSound.setVolume(0);
        _winSound.setVolume(0);
        _coinSound.setVolume(0);
        BackGroundMusic.setVolume(0);
    }

}