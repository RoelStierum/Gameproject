#pragma once

#include <SFML/Graphics.hpp>
#include "../State.hpp"
#include "../Game.hpp"
#include "../Character.hpp"

namespace engine{



	class TestLevel: public State{
	public:
		float gravity = 20.0f;

		sf::Vector2f start = {100,-200};

		TestLevel(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite platform;

		Character character;
	};

}
