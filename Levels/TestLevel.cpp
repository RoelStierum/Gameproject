#include "TestLevel.hpp"
#include "../DEFINITIONS.hpp"

#include <iostream>

namespace engine{



	//Definitions for TestLevel
	TestLevel::TestLevel(GameDataRef data):
			_data(data)
	{
		_data->assets.LoadTexture("TestLevel Character", TESTLEVEL_CHARACTER_FILEPATH);
		_data->assets.LoadTexture("TestLevel Character Flip", TESTLEVEL_CHARACTER_FLIP_FILEPATH);
		character.setPosition(sf::Vector2f {start});
		character.setTexture(_data->assets.GetTexture("TestLevel Character"),_data->assets.GetTexture("TestLevel Character Flip"));
	}

	void TestLevel::Init() {
		_data->assets.LoadTexture("TestLevel Background", TESTLEVEL_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("TestLevel Background"));
		_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

		_data->assets.LoadTexture("TestLevel Platform", TESTLEVEL_PLATFORM_FILEPATH);
		platform.setTexture(_data->assets.GetTexture("TestLevel Platform"));
		platform.setPosition(50,400);
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
			//A of left-arrow voor naar links gaan
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			character.velocity.x = -character.speed;
		}
			//D of right-arrow voor naar rechts gaan
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
			character.velocity.x = character.speed;
		}
			//Stoppen met bewegen als er geen knoppen worden ingedrukt
		else{
			character.velocity.x = 0;
		}

			//Space of up-arrow voor jumpen
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && character.jump < character.max_jump && not character.jump_done){
			character.velocity.y = -character.jump_speed;
			character.jump++;
			character.jump_done = true;
		}

		//Jump reset zodat de speler meerdere keer kan springen als het nodig is.
		if(character.jump_done && not (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))){
			character.jump_done = false;
		}

		//Als de volgende move van de player in het platform zit

		sf::Sprite temp = character.nextSprite(character.velocity * dt);

		if(temp.getGlobalBounds().intersects(platform.getGlobalBounds())){

			//rechts
			if(character.getPosition().x > platform.getPosition().x + platform.getGlobalBounds().width){
				character.velocity.x = 0;
			}
			//links
			else if(character.getPosition().x + character.width < platform.getPosition().x ){
				character.velocity.x = 0;
			}
			else if(character.getPosition().y > platform.getPosition().y + platform.getGlobalBounds().height){
				character.velocity.y = 0;
			}
			else{
				character.velocity.y = 0;
				character.jump = 0;
			}

		}//Als de player niet het platform raakt
		else{
			character.velocity.y += gravity;
		}

		//delete temp;

		///Scherm links en recht collision
		//links
		if(character.nextPosition(character.velocity * dt).x < 0){
			character.velocity.x = 0;
		}
		//rechts
		if(character.nextPosition(character.velocity * dt).x + character.width > SCREEN_WIDTH){
			character.velocity.x = 0;
		}

		//Velocity update
		if(character.velocity != sf::Vector2f{0,0}){
			character.move(character.velocity * dt);
		}

		//player under screen
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


}