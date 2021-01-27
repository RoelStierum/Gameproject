#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <iostream>

namespace engine{

	///@brief FinishState Class.
	///@details State that will be switched to when the player reaches the finish of a level.
	class FinishState: public State{
	public:
		///@brief Constructor for the FinishState class.
		///@param data , gets the game data.
		///@param tijd , gets the time it took the player to reach the finish.
		///@param levelNumber, gets the number of the level to get the highscore of the right level.
		FinishState(GameDataRef data, const float& tijd, const int& levelNumber);

		///@brief Init() function.
		///@details Function that runs on the initialization of the class.
		void Init();

		///@brief HandleInput() function.
		///@details Function that handles all the button clicks.
		void HandleInput();

		void Update(float dt) {}

		///@brief Draw(float dt) function.
		///@details Draws all the objects.
		void Draw(float dt);

	private:
		GameDataRef _data;
        float tijd;
        sf::Text tijdText;

		float _bestTime;
		sf::Text bestTimeText;

		sf::View InitView;

		sf::Sprite _background;

		sf::Sprite _play_next_level;
		sf::Sprite _quit;
		sf::Sprite _menu;

		bool _hoverNextLevel = false;
		bool _hoverQuit = false;
		bool _hoverMainMenu = false;

		bool previousBestText = true;

		int lastLevel = 0;
	};

}