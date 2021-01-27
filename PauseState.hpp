#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <iostream>

namespace engine{

	///@brief PauseState Class.
	///@details State that will be switched to when the player clicks the pause button.
	class PauseState: public State{
	public:

		///@brief Constructor for the FinishState class.
		///@param data , gets the game data.
		PauseState(GameDataRef data);

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

		sf::View InitView;

		sf::Sprite _background;

		sf::Sprite _paused;
		sf::Sprite _resume;
		sf::Sprite _quit;
		sf::Sprite _menu;

		bool _hoverResume = false;
		bool _hoverQuit = false;
		bool _hoverMainMenu = false;
	};

}