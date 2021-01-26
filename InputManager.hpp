#pragma once

#include <SFML/Graphics.hpp>

namespace engine{

    class InputManager {
    public:
        InputManager() {}

        ~InputManager() {}

        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &renderWindow);
		bool HoverOverButton(sf::Sprite object, sf::RenderWindow &renderWindow);

		bool _hoverPlay = false;
		bool _hoverQuit = false;
		bool _hoverMainMenu = false;
		bool _hoverNextLevel = false;
		bool _hoverResume = false;

		sf::Vector2i GetMousePosition(sf::RenderWindow& renderWindow);
    };
}