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

	void InputManager::characterKeyboardInput(Character &character) {
		//A of left-arrow voor naar links gaan
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			if(character.velocity.x <= -character.speed){
				character.velocity.x = -character.speed;
			}else{
				character.velocity.x += -character.speed_up;
			}

		}
			//D of right-arrow voor naar rechts gaan
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			if(character.velocity.x >= character.speed){
				character.velocity.x = character.speed;
			}else{
				character.velocity.x += character.speed_up;
			}
		}
			//Stoppen met bewegen als er geen knoppen worden ingedrukt
		else{
			if (character.velocity.x > character.slow_down) {
				character.velocity.x -= character.slow_down;
			}else if (character.velocity.x < -character.slow_down) {
				character.velocity.x += character.slow_down;
			}else{
				character.velocity.x = 0;
			}
		}

		//Space of up-arrow voor jumpen
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && character.jump < character.max_jump && not character.jump_done){
			if(character.on_ground && character.jump == 0){
				character.velocity.y = -character.jump_speed;
				character.jump++;
				character.jump_done = true;
			}else if(!character.on_ground && character.jump > 0){
				character.velocity.y = -character.jump_speed;
				character.jump++;
				character.jump_done = true;
			}

		}

		//Jump reset zodat de speler meerdere keer kan springen als het nodig is.
		if(character.jump_done && not (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))){
			character.jump_done = false;
		}
	}

}