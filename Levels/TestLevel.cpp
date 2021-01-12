#include "TestLevel.hpp"
#include "../DEFINITIONS.hpp"

#include <iostream>

namespace engine{

	//Definitions for Character
	Character::Character(const sf::Vector2f &position,  const sf::Texture &texture) :
			position(position),
			texture(texture)
	{
		sprite.setTexture(texture);
		sprite.setPosition(position);
		width = sprite.getGlobalBounds().width;
		height = sprite.getGlobalBounds().height;
	}

	Character::Character():
		position(0,0)
	{}

	void Character::setTexture(sf::Texture &texture_) {
		texture = texture_;
		sprite.setTexture(texture);
		width = sprite.getGlobalBounds().width;
		height = sprite.getGlobalBounds().height;
	}

	void Character::setPosition(const sf::Vector2f &position_) {
		position = position_;
		sprite.setPosition(position);
	}

	void Character::draw(sf::RenderWindow& renderWindow) {
		renderWindow.draw(sprite);
	}

	void Character::move(sf::Vector2f movement) {
		position += movement;
		sprite.setPosition(position);
	}

	sf::Sprite& Character::getSprite() {
		return sprite;
	}

	//Definitions for TestLevel
	TestLevel::TestLevel(GameDataRef data):
			_data(data)
	{
		_data->assets.LoadTexture("TestLevel Character", TESTLEVEL_CHARACTER_FILEPATH);
		character.setPosition(sf::Vector2f {400,0});
		character.setTexture(_data->assets.GetTexture("TestLevel Character"));
	}

	void TestLevel::Init() {
		_data->assets.LoadTexture("TestLevel Background", TESTLEVEL_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("TestLevel Background"));
		_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

		_data->assets.LoadTexture("TestLevel Platform", TESTLEVEL_PLATFORM_FILEPATH);
		platform.setTexture(_data->assets.GetTexture("TestLevel Platform"));
		platform.setPosition(200,400);
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
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && character.jump < character.max_jump && not jump_done){
			character.velocity.y = -character.jump_speed;
			character.jump++;
			jump_done = true;
		}

		//Jump reset zodat de speler meerdere keer kan springen als het nodig is.
		if(jump_done && not (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))){
			jump_done = false;
		}

		/*//Als de player het platform heeft geraakt, dan zal de player stoppen met vallen
		//Als de player boven het platform zit zal de y velocity versnellen
		if((character.getPosition().y + character.height) < platform.getPosition().y){
			character.velocity.y += gravity;
		}
		//Als de player het platform raakt zal de velocity 0 worden.
		else{
			if(character.velocity.y > 0){
				character.velocity.y = 0;
				character.jump = 0;
			}
		}*/

		//Als de player in het platform zit
		/*if(character.getSprite().getGlobalBounds().intersects(platform.getGlobalBounds())){
			//Als de player het platform raakt zal de velocity 0 worden.
			if(character.velocity.y > 0){
				character.velocity.y = 0;
				character.jump = 0;
			}
		}*/

		if (		character.getPosition().x + character.width > platform.getPosition().x &&
					character.getPosition().y + character.height > platform.getPosition().y &&
					character.getPosition().x < platform.getPosition().x + platform.getGlobalBounds().width /2){
			std::cout << "left wall \n";
			character.velocity.x = 0;
			//links
		}else if( 	character.getPosition().x < platform.getPosition().x + platform.getGlobalBounds().width &&
					character.getPosition().y + character.height > platform.getPosition().y &&
					character.getPosition().x > platform.getPosition().x + platform.getGlobalBounds().width /2){
			std::cout << "right wall \n";
			character.velocity.x = 0;
			//rechts
		}
		//Als de player niet het platform raakt
		else{
			character.velocity.y += gravity;
		}


		if(character.velocity != sf::Vector2f{0,0}){
			character.move(character.velocity * dt);
		}

		if (character.getPosition().y > SCREEN_HEIGHT + 100){
			character.setPosition(character.getPosition().x, 0);
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