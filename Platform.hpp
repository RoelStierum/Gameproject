#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>

namespace engine {

	class Platform {
	public:
		Platform(GameDataRef data);

		void addPlatform(sf::Texture& texture, const sf::Vector2f& position);

		std::vector<sf::Sprite>& getPlatforms();

		void draw();

	private:
		GameDataRef _data;
		std::vector<sf::Sprite> platformSprites;

	};

}