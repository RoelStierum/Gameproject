#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../DEFINITIONS.hpp"
#include "../State.hpp"
#include "../Game.hpp"
#include "../Character.hpp"
#include "../Platform.hpp"

namespace engine{

	class TestLevel: public State{
	public:
		float gravity = 25.0f;

		sf::Vector2f start = {100,-200};

		TestLevel(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::View CameraPosition;
		float cameraX, cameraY = 0;

		//std::vector<sf::Sprite> platforms;
		Platform platforms = {_data};

		Character character;

		void characterEndgeOfScreen(const Character& character_, const float& dt);
	};

}
