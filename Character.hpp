#pragma once //Character.hpp

#include <SFML/Graphics.hpp>

namespace engine{

	class Character{
	private:
		sf::Sprite sprite;
		sf::Vector2f position;
		sf::Texture texture;
		sf::Texture texture_flip;

		bool flip = false;

		void flipTexture();

	public:
		sf::Vector2f velocity = {0,0};
		float speed = 300.0f;
		float jump_speed = 500.0f;
		int height, width, max_jump =1, jump = 0;
		bool jump_done = false;

		Character(const sf::Vector2f &position, const sf::Texture &texture, const sf::Texture &texture_flip);

		Character();

		void setTexture(sf::Texture& texture_, sf::Texture &texture_flip_);

		void setPosition(const sf::Vector2f& position_);

		void setPosition(const float& x, const float& y);

		sf::Vector2f getPosition();

		void draw(sf::RenderWindow& renderWindow);

		void move(sf::Vector2f movement);

		void move(const float& x, const float& y);

		sf::Vector2f nextPosition(sf::Vector2f movement);

		sf::Sprite nextSprite(sf::Vector2f movement);

		sf::Sprite& getSprite();

		void objectCollisionAndFalling(const sf::Sprite &object, const float& gravity, const float& dt);

		void updateVelocity(const float& dt);
	};

}

