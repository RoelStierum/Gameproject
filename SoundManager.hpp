#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

namespace engine {

	class SoundManager {
	public:
        sf::Sound _hitSound;
        sf::Sound _pointSound;
        sf::Sound _wingSound;
        sf::Sound _deathSound;

		SoundManager();

		~SoundManager() {}

		void CheckSoundLoading();

		void SetSoundBuffers();



	private:
		sf::SoundBuffer _hitSoundBuffer;
		sf::SoundBuffer _pointSoundBuffer;
		sf::SoundBuffer _wingSoundBuffer;
		sf::SoundBuffer _deathSoundBuffer;


	};

}