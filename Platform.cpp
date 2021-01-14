#include "Platform.hpp"

namespace engine
{
	Platform::Platform(GameDataRef data) : _data(data){}

	void Platform::addPlatform(sf::Texture& texture, const sf::Vector2f& position) {
		sf::Sprite platform;
		platform.setTexture(texture);
		platform.setPosition(position);
		platformSprites.push_back(platform);
	}

	std::vector<sf::Sprite>& Platform::getPlatforms() {
		return platformSprites;
	}

	void Platform::draw(){
		for (sf::Sprite platform : platformSprites){
			_data->renderWindow.draw(platform);
		}
	}
}