#pragma once

#include <SFML/Graphics.hpp>

namespace engine{

    class InputManager {
    public:
        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &renderWindow);

        sf::Vector2i GetMousePosition(sf::RenderWindow& renderWindow);
    };
}