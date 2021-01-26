#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace engine{

    class MainMenuState: public State{
    public:
        MainMenuState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;

        sf::Texture _backgroundTexture;
        sf::Sprite _background;

        sf::Sprite _title;
        sf::Sprite _play_button;
		sf::Sprite _quit_button;
        sf::Sprite _instructions_button;

		sf::Sprite muteSprite;
		bool mute = false;
        bool mouse = false;
    };

}
