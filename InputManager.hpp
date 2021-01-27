#pragma once

#include <SFML/Graphics.hpp>

namespace engine{

    ///@brief InputManager class
    ///@details This class handles the inputs
    class InputManager {
    public:
        ///@brief IsSpriteClicked function of the InputManager class
        ///@details This function returns a bool if the given object is clicked with the given mouse button and render window.
        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &renderWindow);

        ///@brief IsSpriteClicked function of the InputManager class
        ///@details This function returns a bool if the given object is hovered over with the mouse
		bool HoverOverButton(sf::Sprite object, sf::RenderWindow &renderWindow);
    };
}