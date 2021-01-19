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

		void Init() override;

		void HandleInput() override;
		void Update(float dt) override;
		void Draw(float dt) override;

        void Pause() override;
        void Resume() override;

        void restart();

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::View CameraPosition;
		float cameraX, cameraY = 0;

		Platform platforms = {_data};

		Character character;

        sf::Sprite pauseButton;
		sf::Sprite coin;

		void characterEndgeOfScreen(const Character& character_, const float& dt);
	};

}
