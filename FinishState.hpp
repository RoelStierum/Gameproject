#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <iostream>

namespace engine{

	class FinishState: public State{
	public:
		FinishState(GameDataRef data,const float& tijd);

		void Init();

		void HandleInput();

		void Update(float dt) {
		}

		void Draw(float dt);

	private:
		GameDataRef _data;
        float tijd;
        sf::Text tijdText;

		sf::View InitView;

		sf::Sprite _background;

		sf::Sprite _play_again;
		sf::Sprite _quit;
		sf::Sprite _menu;
	};

}