#include "Character.hpp" //Character.cpp

#include "DEFINITIONS.hpp"
#include "iostream"

namespace engine{

	//Definitions for Character
	Character::Character(GameDataRef data, const sf::Vector2f &position,  const sf::Texture &texture, const sf::Texture &texture_flip) :
            _data(data),
	        position(position),
			texture(texture),
			texture_flip(texture_flip)
	{
		sprite.setTexture(texture);
		sprite.setPosition(position);
		width = sprite.getGlobalBounds().width;
		height = sprite.getGlobalBounds().height;
	}

	Character::Character(GameDataRef data):
			_data(data),
			position(0,0)
	{}

	void Character::flipTexture() {
		if(flip){
			sprite.setTexture(texture);
		}else{
			sprite.setTexture(texture_flip);
		}
		flip = !flip;
	}

	void Character::setTexture(sf::Texture &texture_, sf::Texture &texture_flip_) {
		texture = texture_;
		texture_flip = texture_flip_;
		sprite.setTexture(texture);
		width = sprite.getGlobalBounds().width;
		height = sprite.getGlobalBounds().height;
	}

	void Character::setPosition(const sf::Vector2f &position_) {
		position = position_;
		sprite.setPosition(position);
	}

	void Character::setPosition(const float &x, const float &y) {
		position.x = x;
		position.y = y;
		sprite.setPosition(position);
	}

	sf::Vector2f Character::getPosition(){
		return position;
	}

	void Character::draw(sf::RenderWindow& renderWindow) {
		renderWindow.draw(sprite);
	}

	void Character::move(sf::Vector2f movement) {
		position += movement;
		if(movement.x < 0 && !flip){
			flipTexture();
		}else if(movement.x > 0 && flip){
			flipTexture();
		}
		sprite.setPosition(position);
	}

	void Character::move(const float &x, const float &y) {
		position.x += x;
		position.y += y;
		sprite.setPosition(position);
	}

	sf::Vector2f Character::nextPosition(sf::Vector2f movement) {
		return position + movement;
	}

	sf::Sprite Character::nextSprite(sf::Vector2f movement) {
		sf::Sprite temp;
		temp.setTextureRect(sprite.getTextureRect());
		temp.setPosition(position + movement);
		return temp;
	}

	sf::Sprite& Character::getSprite() {
		return sprite;
	}
	
	bool Character::objectCollisionAndFalling(const sf::Sprite &object, const float& dt) {
		//Als de volgende move van de player in het object zit

		sf::Sprite temp = nextSprite(velocity * dt);

		if(temp.getGlobalBounds().intersects(object.getGlobalBounds())){
			//rechts
			if(getPosition().x> object.getPosition().x + object.getGlobalBounds().width
					&& getPosition().y + height  - 1 >= object.getPosition().y){
				velocity.x = 0;
			}
				//links
			else if(getPosition().x + width < object.getPosition().x
					&& getPosition().y + height - 1 >= object.getPosition().y){
				velocity.x = 0;
			}
				//onderkant
			else if(getPosition().y > object.getPosition().y + object.getGlobalBounds().height){
				velocity.y = 0;
			}
				//bovenkant
			else{
				velocity.y = 0;
				jump = 0;
				on_ground = true;
			}
			return true;
		}//Als de player niet het object raakt
		else{
			return false;
		}

		//delete temp;
	}
	
	void Character::updateVelocity(const float &dt) {
		//Velocity update
		if(velocity != sf::Vector2f{0,0}){
			move(velocity * dt);
		}
	}

	void Character::respawn(sf::Vector2f spawn) {
		setPosition(spawn);
		velocity.x = 0;
	}

    void Character::characterKeyboardInput() {
        //A of left-arrow voor naar links gaan
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if(velocity.x <= -speed){
                velocity.x = -speed;
            }else{
                velocity.x += -speed_up;
            }

        }
            //D of right-arrow voor naar rechts gaan
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if(velocity.x >= speed){
                velocity.x = speed;
            }else{
                velocity.x += speed_up;
            }
        }
            //Stoppen met bewegen als er geen knoppen worden ingedrukt
        else{
            if (velocity.x > slow_down) {
                velocity.x -= slow_down;
            }else if (velocity.x < -slow_down) {
                velocity.x += slow_down;
            }else{
                velocity.x = 0;
            }
        }

        //Space of up-arrow voor jumpen
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && jump < max_jump && not jump_done){
            _data->sound._hitSound.play();
            _data->sound._hitSound.setVolume(50);
            if(on_ground && jump == 0){
                velocity.y = -jump_speed;
                jump++;
                jump_done = true;
            }else if(!on_ground && jump > 0){
                velocity.y = -jump_speed;
                jump++;
                jump_done = true;
            }

        }

        //Jump reset zodat de speler meerdere keer kan springen als het nodig is.
        if(jump_done && not (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))){
            jump_done = false;
        }
    }

}