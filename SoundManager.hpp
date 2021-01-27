#pragma once

#include <SFML/Audio.hpp>
#include <iostream>

namespace engine {

	///@brief SoundManager Class
	///@details Class to manage all the sound effects and background music in the game.
	class SoundManager {
	public:
		///@brief Sound effect for when the player jumps.
        sf::Sound _jumpSound;
		///@brief Sound effect for when the player falls off a platform and dies.
        sf::Sound _deathSound;
		///@brief Sound effect for when the player gets a powerup.
        sf::Sound _powerupSound;
		///@brief Sound effect for when the player clicks a button
        sf::Sound _clickButtonSound;
		///@brief Sound effect for when the player reaches the flag at the end of a level.
        sf::Sound _flagSound;
		///@brief Background music for the game.
        sf::Music BackGroundMusic;

		///@brief Constructor for the Soundmanager class.
		///@details This constructor runs some necessary functions.
		///@details CheckSoundLoading() runs to check if the all the sounds are loaded correctly.
		///@details SetSoundBuffers() runs so that all the sounds are loaded by default.
		///@details setVolume() runs so that the volume of the sounds and music is optimal.
		///@details BackGroundMusic.setLoop(true) is done so that the backgroundmusic loops.
		SoundManager();

		///@brief setVolume() function.
		///@details Function to be able to adjust the volume of the sound effects and music.
        void setVolume();

		///@brief mute() function.
		///@details Function to be able to mute all the in game sounds.
        void mute();

	private:
		sf::SoundBuffer _jumpSoundBuffer;
		sf::SoundBuffer _deathSoundBuffer;
        sf::SoundBuffer _powerupSoundBuffer;
        sf::SoundBuffer _clickButtonSoundBuffer;
        sf::SoundBuffer _flagSoundBuffer;

        void CheckSoundLoading();

        void SetSoundBuffers();

	};

}