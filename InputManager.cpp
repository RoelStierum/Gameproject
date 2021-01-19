#include "InputManager.hpp"

namespace engine{

    bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &renderWindow){
        if(sf::Mouse::isButtonPressed(button)){
            sf::IntRect temp_rect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

            if(temp_rect.contains(sf::Mouse::getPosition(renderWindow))){
                return true;
            }
        }
        return false;
    }

    sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& renderWindow){
        return sf::Mouse::getPosition(renderWindow);
    }

}