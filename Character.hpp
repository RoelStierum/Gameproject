#pragma once //Character.hpp

#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace engine{

	class Character{
	private:
	    //Game data
	    GameDataRef _data;

	    //Sprite for character
		sf::Sprite sprite;

		//Textures for character
		sf::Vector2f position;
		sf::Texture texture;
		sf::Texture texture_flip;
        sf::Texture run_right1;
        sf::Texture run_right2;
        sf::Texture run_left1;
        sf::Texture run_left2;

        // Flip bool for knowing the texture direction
		bool flip = false;

		//Clock for switching texture while running
		sf::Clock animationClock;
		// int for looping the textures
        int animationRun = 0;
        //Bool for knowing when the air texture is active
        bool air_texture = false;

        //funtion for flipping flip bool and setting the texture
		void flipTexture();


	public:
	    ///@brief Velocity of the character
		sf::Vector2f velocity = {0,0};
	    ///@brief Max speed of the character
		float speed = 400.0f;
		///@brief Jump power
		float jump_speed = 600.0f;
		///@brief Slow down of the character on the ground and in the air
		float slow_down = 0.0f, slow_down_ground = 40.0f, slow_down_air = 5.0f;
        ///@brief Speed up of the character on the ground and in the air
        float speed_up = 0.0f, speed_up_ground = 40.0f, speed_up_air = 30.0f;
        ///@brief The max jump amount and the current jump amount
		int max_jump =1, jump = 0;
		///@brief The Jump done bool and the on ground bool
		bool jump_done = false, on_ground = false;

		//Character(GameDataRef data, const sf::Vector2f &position, const sf::Texture &texture, const sf::Texture &texture_flip);

		///@brief Constructor of the Character class.
		///@details This constructor initializes the Character class.
		///@par data This is the game data.
		Character(GameDataRef data);

		///@brief Update function of the Character class.
		///@details This function runs on every update cycle of the game and updates the texture for animations.
		void update();

		///@brief setTexture function of the Character class.
		///@details This function initializes the textures of the character.
		///@warning This function has to be run in the initializer of the level.
		void setTexture(
                sf::Texture &texture_,
                sf::Texture &texture_flip_,
                sf::Texture &texture_run_right1,
                sf::Texture &texture_run_right2,
                sf::Texture &texture_run_left1,
                sf::Texture &texture_run_left2
        );

		///@brief setPosition function of the Character class.
		///@details This function sets the position of the character to the given vector.
		///@see setPosition
		void setPosition(const sf::Vector2f& position_);

        ///@brief setPosition function of the Character class.
        ///@details This function sets the position of the character to the given floats.
        ///@see setPosition
        void setPosition(const float& x, const float& y);

		sf::Vector2f getPosition();

		void draw(sf::RenderWindow& renderWindow);

		void move(sf::Vector2f movement);

		void move(const float& x, const float& y);

		sf::Vector2f nextPosition(sf::Vector2f movement);

		sf::Sprite nextSprite(sf::Vector2f movement);

		sf::Sprite& getSprite();

		bool objectCollisionAndFalling(const sf::Sprite &object, const float& dt);

		void updateVelocity(const float& dt);

		void respawn(sf::Vector2f spawn);

        void characterKeyboardInput();
	};

}

