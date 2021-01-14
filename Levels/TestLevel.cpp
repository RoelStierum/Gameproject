#include "TestLevel.hpp"
#include "../DEFINITIONS.hpp"
#include "../TestState.hpp"

#include <iostream>

namespace engine{

	//Definitions for TestLevel
	TestLevel::TestLevel(GameDataRef data):
			_data(data)
	{}

	void TestLevel::Init() {
		_data->assets.LoadTexture("TestLevel Background", TESTLEVEL_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("TestLevel Background"));
		//_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

		_data->assets.LoadTexture("TestLevel Platform", TESTLEVEL_PLATFORM_FILEPATH);
		_data->assets.LoadTexture("TestLevel Platform 2", TESTLEVEL_PLATFORM2_FILEPATH);

		for(float i = 50; i + 487 < 15875 ; i += 200 + 300){
			platforms.addPlatform(
					_data->assets.GetTexture("TestLevel Platform 2"),
					sf::Vector2f{i,400}
			);
		}


		_data->assets.LoadTexture("TestLevel Character", TESTLEVEL_CHARACTER_FILEPATH);
		_data->assets.LoadTexture("TestLevel Character Flip", TESTLEVEL_CHARACTER_FLIP_FILEPATH);
		character.setPosition(sf::Vector2f {start});
		character.setTexture(_data->assets.GetTexture("TestLevel Character"),_data->assets.GetTexture("TestLevel Character Flip"));
	}

	void TestLevel::HandleInput() {
		_data->input.characterKeyboardInput(character);
		std::cout << "Velocity:" << character.velocity.x << ", " << character.velocity.y << std::endl;

		sf::Event event;

		while(_data->renderWindow.pollEvent(event)){
			if(sf::Event::Closed == event.type){
				_data->renderWindow.close();
			}
		}
	}

	void TestLevel::Update(float dt) {
		bool collision = false;
		for(sf::Sprite platform : platforms.getPlatforms()){
			if(character.objectCollisionAndFalling(platform, dt)){
				collision = true;
			}
		}
		if(!collision){
			character.velocity.y += gravity;
			character.slow_down = character.slow_down_air;
			character.speed_up = character.speed_up_air;
		}else{
			character.slow_down = character.slow_down_ground;
			character.speed_up = character.speed_up_ground;
		}

		characterEndgeOfScreen(character, dt);

		character.updateVelocity(dt);

		//player under screen / respawn
		if (character.getPosition().y > SCREEN_HEIGHT + 100){
			character.respawn(start);
		}

		//View
		cameraX = -(SCREEN_WIDTH/2) + character.getPosition().x;

		//links camera stoppen
		if(cameraX < 0){
			cameraX = 0;
		}

		//rechts camera stoppen
		else if(cameraX > (_background.getPosition().x + _background.getGlobalBounds().width - (SCREEN_WIDTH))){
			cameraX = _background.getPosition().x + _background.getGlobalBounds().width - (SCREEN_WIDTH);
		}

		CameraPosition.reset(sf::FloatRect(cameraX, cameraY,  SCREEN_WIDTH, SCREEN_HEIGHT));

		//End of game
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
			_data->machine.AddState( StateRef ( new TestState(_data)), false);
		}
	}

	void TestLevel::Draw(float dt) {
		_data->renderWindow.setView(CameraPosition);
		_data->renderWindow.clear();
		_data->renderWindow.draw(_background);
		platforms.draw();
		character.draw(_data->renderWindow);
		_data->renderWindow.display();
	}

	void TestLevel::characterEndgeOfScreen(const Character &character_, const float& dt) {
		//links
		if(character.nextPosition(character.velocity * dt).x < _background.getPosition().x){
			character.velocity.x = 0;
		}
		//rechts
		if(character.nextPosition(character.velocity * dt).x + character.width > _background.getPosition().x + _background.getGlobalBounds().width){
			character.velocity.x = 0;
		}
	}

}