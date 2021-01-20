#include "SoundManager.hpp"
#include "DEFINITIONS.hpp"

namespace engine{

	SoundManager::SoundManager() {
		CheckSoundLoading();
		SetSoundBuffers();
		setVolume();
	}

	void SoundManager::CheckSoundLoading(){
		if ( !_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH) ){
			std::cout << "Error loading hit sound effect\n";
		}if ( !_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH) ){
			std::cout << "Error loading point sound effect\n";
		}if ( !_jumpSoundBuffer.loadFromFile(JUMP_SOUND_FILEPATH) ){
			std::cout << "Error loading wing sound effect\n";
		}if ( !_deathSoundBuffer.loadFromFile(WING_DEATH_FILEPATH) ){
            std::cout << "Error loading death sound effect\n";
        }if ( !_coinSoundBuffer.loadFromFile(COIN_SOUND_FILEPATH) ){
            std::cout << "Error loading coin sound effect\n";
        }

        if ( !_clickSoundBuffer.loadFromFile(CLICK_SOUND_FILEPATH) ){
            std::cout << "Error loading click sound effect\n";
        }
        if ( !_winSoundBuffer.loadFromFile(WIN_SOUND_FILEPATH) ){
            std::cout << "Error loading click sound effect\n";
        }

		if(!TestLevelMusic.openFromFile(MUSIC_FILEPATH)){
            std::cout << "Error loading music\n";
		}
	}

	void SoundManager::SetSoundBuffers(){
		_hitSound.setBuffer( _hitSoundBuffer );
		_pointSound.setBuffer( _pointSoundBuffer );
		_jumpSound.setBuffer( _jumpSoundBuffer );
		_deathSound.setBuffer(_deathSoundBuffer);
		_coinSound.setBuffer(_coinSoundBuffer);
		_clickSound.setBuffer(_clickSoundBuffer);
		_winSound.setBuffer(_winSoundBuffer);
	}

	void SoundManager::setVolume() {
		_coinSound.setVolume(20);
        _jumpSound.setVolume(20);
        TestLevelMusic.setVolume(25);
        _deathSound.setVolume(20);
        TestLevelMusic.setLoop(true);
	}

}