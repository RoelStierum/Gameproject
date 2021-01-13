#include "TestLevel.hpp"
#include "../DEFINITIONS.hpp"

#include <iostream>

namespace engine{

	//Definitions for TestLevel
	TestLevel::TestLevel(GameDataRef data):
			_data(data)
	{}

	void TestLevel::Init() {
		_data->assets.LoadTexture("TestLevel Background", TESTLEVEL_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("TestLevel Background"));
		_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

		_data->assets.LoadTexture("TestLevel Platform", TESTLEVEL_PLATFORM_FILEPATH);
		platform.setTexture(_data->assets.GetTexture("TestLevel Platform"));
		platform.setPosition(50,400);

		_data->assets.LoadTexture("TestLevel Character", TESTLEVEL_CHARACTER_FILEPATH);
		_data->assets.LoadTexture("TestLevel Character Flip", TESTLEVEL_CHARACTER_FLIP_FILEPATH);
		character.setPosition(sf::Vector2f {start});
		character.setTexture(_data->assets.GetTexture("TestLevel Character"),_data->assets.GetTexture("TestLevel Character Flip"));
	}

	void TestLevel::HandleInput() {
		sf::Event event;

		while(_data->renderWindow.pollEvent(event)){
			if(sf::Event::Closed == event.type){
				_data->renderWindow.close();
			}
		}
	}

	void TestLevel::Update(float dt) {
		_data->input.characterKeyboardInput(character);

		character.objectCollisionAndFalling(platform, gravity, dt);

		characterEndgeOfScreen(character, dt);

		character.updateVelocity(dt);

		//player under screen / respawn
		if (character.getPosition().y > SCREEN_HEIGHT + 100){
			character.setPosition(start);
		}
	}

	void TestLevel::Draw(float dt) {
		_data->renderWindow.clear();
		_data->renderWindow.draw(_background);
		_data->renderWindow.draw(platform);
		character.draw(_data->renderWindow);
		_data->renderWindow.display();
	}

	void TestLevel::characterEndgeOfScreen(const Character &character_, const float& dt) {
		//links
		if(character.nextPosition(character.velocity * dt).x < 0){
			character.velocity.x = 0;
		}
		//rechts
		if(character.nextPosition(character.velocity * dt).x + character.width > SCREEN_WIDTH){
			character.velocity.x = 0;
		}
	}

}