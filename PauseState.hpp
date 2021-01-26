#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <iostream>

namespace engine{

	class PauseState: public State{
	public:
		PauseState(GameDataRef data);

		void Init();

		void HandleInput();

		void Update(float dt) {}

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