#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../DEFINITIONS.hpp"
#include "../State.hpp"
#include "../Game.hpp"
#include "../Character.hpp"
#include "../Platform.hpp"

namespace engine{

	///@brief Level3 class.
	///@details This class is a template for a level.
	class Level3: public State{
	public:
		///@brief gravity Member
		///@details This gravity member is for the acceleration of the objects.
		float gravity = 1500; //25.0f;

		///@brief start Member
		///@details This start member is the start position of the character
		sf::Vector2f start = {100,-200};

		///@brief Level3 class constructor
		///@details This constructor sets the _data member.
		///@param data GameDataRef for the _data member.
		Level3(GameDataRef data);

		///@brief Init function of the Level3 class.
		///@details Function that runs on the initialization of the class.
		void Init() override;

		///@brief HandleInput function of the Level3 class.
		///@details Function that handles all the inputs.
		void HandleInput() override;

		///@brief Update function of the Level3 class.
		///@details Function that handles all the updates.
		void Update(float dt) override;

		///@brief Draw function of the Level3 class.
		///@details Function that handles the drawing on the render window.
		void Draw(float dt) override;

		///@brief Pause function of the Level3 class.
		///@details Function that runs when the state is set to paused.
		void Pause() override;

		///@brief Resume function of the Level3 class.
		///@details Function that runs when the state is resumed.
		void Resume() override;

		///@brief restart function of the Level3 class.
		///@details Function that runs when the level is reset.
		void restart();

	private:
		GameDataRef _data;

		sf::Sprite _background;
		sf::View CameraPosition;
		float cameraX, cameraY = 0;

		Platform platforms = {_data};

		//flag and clock
		sf::Sprite flag;
		sf::Clock clockFinish;
		bool finished = false;

		Character character;

		sf::Sprite pauseButton;

		//tijd van de het level
		sf::Clock levelTime;
		sf::Text levelTimeText;
		float tijd = 0;

		int levelNumber = 3;

		void characterEdgeOfScreen(const Character& character_, const float& dt);

	};

}