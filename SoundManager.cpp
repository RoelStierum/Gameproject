#include "SoundManager.hpp"
#include "DEFINITIONS.hpp"

namespace engine{

	SoundManager::SoundManager() {
		CheckSoundLoading();
		SetSoundBuffers();
	}

	void SoundManager::CheckSoundLoading(){
		if ( !_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH) ){
			std::cout << "Error loading hit sound effect\n";
		}if ( !_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH) ){
			std::cout << "Error loading point sound effect\n";
		}if ( !_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH) ){
			std::cout << "Error loading wing sound effect\n";
		}
	}

	void SoundManager::SetSoundBuffers(){
		_hitSound.setBuffer( _hitSoundBuffer );
		_pointSound.setBuffer( _pointSoundBuffer );
		_wingSound.setBuffer( _wingSoundBuffer );
	}

}