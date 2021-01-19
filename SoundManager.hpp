#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

namespace engine {

	class SoundManager {
	public:
        sf::Sound _hitSound;
        sf::Sound _pointSound;
        sf::Sound _jumpSound;
        sf::Sound _deathSound;
        sf::Sound _coinSound;

        sf::Music TestLevelMusic;

		SoundManager();

		~SoundManager() {}





	private:
		sf::SoundBuffer _hitSoundBuffer;
		sf::SoundBuffer _pointSoundBuffer;
		sf::SoundBuffer _jumpSoundBuffer;
		sf::SoundBuffer _deathSoundBuffer;
        sf::SoundBuffer _coinSoundBuffer;

        void CheckSoundLoading();

        void SetSoundBuffers();

        void setVolume();
	};

}