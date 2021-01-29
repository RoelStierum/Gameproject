#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace engine{

	///@brief MainMenuState Class.
	///@details State that will be switched to when the splash state timer is over or the player clicks the main menu button.
	class MainMenuState: public State{
    public:
		///@brief Constructor for the MainMenuState class.
		///@param data , gets the game data.
        MainMenuState(GameDataRef data);

		///@brief Init() function.
		///@details Function that runs on the initialization of the class.
		void Init();

		///@brief HandleInput() function.
		///@details Function that handles all the button clicks.
		void HandleInput();

        void Update(float dt){}

		///@brief Draw(float dt) function.
		///@details Draws all the objects.
        void Draw(float dt);

    private:
        GameDataRef _data;

        sf::Sprite _background;

        sf::Sprite _title;
        sf::Sprite _play_button;
		sf::Sprite _quit_button;
        sf::Sprite _instructions_button;


		sf::Sprite muteSprite;
		bool mute = false;

		bool _hoverPlay = false;
		bool _hoverQuit = false;
		bool _hoverInstructions = false;
        bool mouseCheck = true;
    };

}
