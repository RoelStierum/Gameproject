#pragma once

#include <SFML/Graphics.hpp>
#include "../State.hpp"
#include "../Game.hpp"

namespace engine{

	class Character{
	private:
		sf::Sprite sprite;
		sf::Vector2f position;
		sf::Texture texture;



	public:
		sf::Vector2f velocity = {0,0};
		float speed = 300.0f;
		float jump_speed = 500.0f;
		int height, width, max_jump =1, jump = 0;

		Character(const sf::Vector2f &position, const sf::Texture &texture);

		Character();

		void setTexture(sf::Texture& texture_);

		void setPosition(const sf::Vector2f& position_);

		void setPosition(const float& x, const float& y){
			position.x = x;
			position.y = y;
			sprite.setPosition(position);
		}

		sf::Vector2f getPosition(){
			return position;
		}

		void draw(sf::RenderWindow& renderWindow);

		void move(sf::Vector2f movement);

		void move(const float& x, const float& y){
			position.x += x;
			position.y += y;
			sprite.setPosition(position);
		}

		sf::Sprite& getSprite();
	};

	class TestLevel: public State{
	public:
		float gravity = 20.0f;
		bool jump_done = false;

		TestLevel(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite platform;

		Character character;
	};

}
