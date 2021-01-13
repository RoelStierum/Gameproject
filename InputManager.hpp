#pragma once

#include <SFML/Graphics.hpp>
#include "Character.hpp"

namespace engine{

    class InputManager {
    public:
        InputManager() {}

        ~InputManager() {}

        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &renderWindow);

        sf::Vector2i GetMousePosition(sf::RenderWindow& renderWindow);

        void characterKeyboardInput(engine::Character& character);
    };
}