#include "InputManager.hpp"

namespace engine{

    //IsSpriteClicked function return a bool if the given object is clicked with the given mouse button and render window.
    bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &renderWindow){
        if(sf::Mouse::isButtonPressed(button)){
            sf::IntRect temp_rect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);

            if(temp_rect.contains(sf::Mouse::getPosition(renderWindow))){
                return true;
            }
        }
        return false;
    }

    //HoverOverButton function return a bool if the given object is hovered over with the mouse
	bool InputManager::HoverOverButton(sf::Sprite object, sf::RenderWindow &renderWindow){
			sf::IntRect temp_rect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
			if(temp_rect.contains(sf::Mouse::getPosition(renderWindow))){
				return true;
			}
		return false;
	}

}