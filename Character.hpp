#pragma once //Character.hpp

#include <SFML/Graphics.hpp>
#include "Game.hpp"

namespace engine{

	class Character{
	private:
	    GameDataRef _data;

		sf::Sprite sprite;
		sf::Vector2f position;
		sf::Texture texture;
		sf::Texture texture_flip;
        sf::Texture run_right1;
        sf::Texture run_right2;
        sf::Texture run_left1;
        sf::Texture run_left2;

		bool flip = false;

		sf::Clock testClock;
        int testRun = 0;
        bool air_texture = false;

		void flipTexture();


	public:
		sf::Vector2f velocity = {0,0};
		float speed = 400.0f;
		float jump_speed = 600.0f;
		float slow_down = 0.0f, slow_down_ground = 40.0f, slow_down_air = 5.0f;
		float speed_up = 0.0f, speed_up_ground = 40.0f, speed_up_air = 30.0f;
		int height, width, max_jump =1, jump = 0;
		bool jump_done = false, on_ground = false;

		//Character(GameDataRef data, const sf::Vector2f &position, const sf::Texture &texture, const sf::Texture &texture_flip);

		Character(GameDataRef data);

		void update();

		void setTexture(
                sf::Texture &texture_,
                sf::Texture &texture_flip_,
                sf::Texture &texture_run_right1,
                sf::Texture &texture_run_right2,
                sf::Texture &texture_run_left1,
                sf::Texture &texture_run_left2
        );

		void setPosition(const sf::Vector2f& position_);

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

