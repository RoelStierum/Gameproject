#include "Character.hpp" //Character.cpp

#include "DEFINITIONS.hpp"
#include "iostream"

namespace engine{

	//Definitions for Character
	/*Character::Character(GameDataRef data, const sf::Vector2f &position,  const sf::Texture &texture, const sf::Texture &texture_flip) :
            _data(data),
	        position(position),
			texture(texture),
			texture_flip(texture_flip)
	{
		sprite.setTexture(texture);
		sprite.setPosition(position);
		width = sprite.getGlobalBounds().width;
		height = sprite.getGlobalBounds().height;
	}*/

	//Constructor of the Character class
	Character::Character(GameDataRef data):
			_data(data),
			position(0,0)
	{}

	//flipTexture funtion for flipping the texture
	void Character::flipTexture() {
		if(flip){
			sprite.setTexture(texture);
		}else{
			sprite.setTexture(texture_flip);
		}
		flip = !flip;
	}

	//update function for animating the character based on the velocity
	void Character::update() {
	    //animationRun loops for the 3 textures of the animation
	    //animationRun = 0 - > 1 - > 2 - > 0

	    if(animationClock.getElapsedTime().asSeconds() > 0.15 && on_ground){
            if(velocity.x == 0){
                if(flip){
                    sprite.setTexture(texture_flip);
                }else {
                    sprite.setTexture(texture);
                }
            }

	        if(animationRun == 0){

	            if(velocity.x > 0){
                    sprite.setTexture(run_right1);
	            }else if (velocity.x < 0){
                    sprite.setTexture(run_left1);
	            }
                animationRun = 1;

	        }else if(animationRun == 1){

                if(velocity.x > 0){
                    sprite.setTexture(run_right2);
                }else if (velocity.x < 0){
                    sprite.setTexture(run_left2);
                }
                animationRun = 2;

            }else if(animationRun == 2){

                if(velocity.x > 0){
                    sprite.setTexture(texture);
                }else if (velocity.x < 0){
                    sprite.setTexture(texture_flip);
                }
                animationRun = 0;

            }else{
	            animationRun = 0;
	        }

            animationClock.restart();
	    }

	    if(on_ground) {
            if (air_texture) {
                air_texture = false;
            }
        }

	    if(!on_ground && !air_texture){
            animationRun = 2;
            if(flip){
                sprite.setTexture(run_left1);
            }else {
                sprite.setTexture(run_right1);
            }
            air_texture = true;
	    }
	}

	//setTexture function for setting the member variables
	void Character::setTexture(
	        sf::Texture &texture_,
	        sf::Texture &texture_flip_,
	        sf::Texture &texture_run_right1,
	        sf::Texture &texture_run_right2,
	        sf::Texture &texture_run_left1,
	        sf::Texture &texture_run_left2
	        ) {
		texture = texture_;
		texture_flip = texture_flip_;
        run_right1 = texture_run_right1;
        run_right2 = texture_run_right2;
        run_left1 = texture_run_left1;
        run_left2 = texture_run_left2;
		sprite.setTexture(texture);
	}

	//setPosition function for setting the position of the character with a sf::Vector2f.
	void Character::setPosition(const sf::Vector2f &position_) {
		position = position_;
		sprite.setPosition(position);
	}

    //setPosition function for setting the position of the character with 2 floats.
	void Character::setPosition(const float &x, const float &y) {
		position.x = x;
		position.y = y;
		sprite.setPosition(position);
	}

	//getPosition function for return the position as a sf::Vector2f.
	sf::Vector2f Character::getPosition(){
		return position;
	}

	//draw function for drawwing the member sprite in the given RenderWindow.
	void Character::draw(sf::RenderWindow& renderWindow) {
		renderWindow.draw(sprite);
	}

	//move function for moving the character relative to the position with a sf::Vector2f.
	void Character::move(sf::Vector2f movement) {
		position += movement;
		if(movement.x < 0 && !flip){
			flipTexture();
		}else if(movement.x > 0 && flip){
			flipTexture();
		}
		sprite.setPosition(position);
	}

    //move function for moving the character relative to the position with 2 floats.
	void Character::move(const float &x, const float &y) {
		position.x += x;
		position.y += y;
		sprite.setPosition(position);
	}

	//nextPosition function for returning a sf::Vector2f of the future position. (Used for collision)
	sf::Vector2f Character::nextPosition(sf::Vector2f movement) {
		return position + movement;
	}

	//nextSprite function for returning a sf::Sprite with the future position. (Used for collision)
	sf::Sprite Character::nextSprite(sf::Vector2f movement) {
		sf::Sprite temp;
		temp.setTextureRect(sprite.getTextureRect());
		temp.setPosition(position + movement);
		return temp;
	}

	//getSprite function for returning the member sprite
	sf::Sprite& Character::getSprite() {
		return sprite;
	}

	//objectCollisionAndFalling function for return a bool if the character is colliding with the object.
	bool Character::objectCollisionAndFalling(const sf::Sprite &object, const float& dt) {
		//Als de volgende move van de player in het object zit

		sf::Sprite temp = nextSprite(velocity * dt);
		bool tmp = false;

		if(temp.getGlobalBounds().intersects(object.getGlobalBounds())) {
            //rechts
            if (getPosition().x > object.getPosition().x + object.getGlobalBounds().width
                && getPosition().y + sprite.getGlobalBounds().height - 1 >= object.getPosition().y) {
                velocity.x = 0;
            }
                //links
            else if (getPosition().x + sprite.getGlobalBounds().width < object.getPosition().x
                     && getPosition().y + sprite.getGlobalBounds().height - 1 >= object.getPosition().y) {
                velocity.x = 0;
            }
                //onderkant
            else if (getPosition().y > object.getPosition().y + object.getGlobalBounds().height) {
                velocity.y = 0;

            }
                //bovenkant
            else {
                if(velocity.y > 50){
                    setPosition(position.x,object.getPosition().y - sprite.getGlobalBounds().height);
                }
                velocity.y = 0;
                jump = 0;
                on_ground = true;
                tmp = true;
            }
        }
		return tmp;
	}

	//updateVelocity function for updating the movement based on the vector and delta time.
	void Character::updateVelocity(const float &dt) {
		//Velocity update
		if(velocity != sf::Vector2f{0,0}){
			move(velocity * dt);
		}
	}

	//respawn function for resetting the character
	void Character::respawn(sf::Vector2f spawn) {
	    max_jump = 1;
		setPosition(spawn);
		velocity.x = 0;
	}

    //characterKeyboardInput function for updating the velocity based on keyboard inputs
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
            if(on_ground && jump == 0){
                _data->sound._jumpSound.play();
                velocity.y = -jump_speed;
                jump++;
                jump_done = true;
            }else if(!on_ground && jump > 0){
                _data->sound._jumpSound.play();
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