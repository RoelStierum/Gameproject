#include "TestLevel.hpp"
#include "../DEFINITIONS.hpp"
#include "../PauseState.hpp"

#include <iostream>

namespace engine{

	//Constructor for TestLevel
	TestLevel::TestLevel(GameDataRef data):
			_data(data),
			character(data)
	{}

	void TestLevel::Init() {
	    ///START MUSIC
	    _data->sound.TestLevelMusic.play();


        ///Background Initializer
		_data->assets.LoadTexture("TestLevel Background", TESTLEVEL_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("TestLevel Background"));
		//_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);


		///Pause button
		_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
		pauseButton.setTexture(_data->assets.GetTexture("Pause Button"));
		pauseButton.setPosition(SCREEN_WIDTH-16-pauseButton.getGlobalBounds().width,16);


        ///Platforms Texture Initializer
		_data->assets.LoadTexture("TestLevel Platform", TESTLEVEL_PLATFORM_FILEPATH);
		_data->assets.LoadTexture("TestLevel Platform 2", TESTLEVEL_PLATFORM2_FILEPATH);
        _data->assets.LoadTexture("TestLevel Platform Vertical", TESTLEVEL_PLATFORM_VERTICAL_FILEPATH);

        ///Platforms Initializer
		platforms.addPlatform( //starting
				_data->assets.GetTexture("TestLevel Platform 2"),
				sf::Vector2f{50,400}
		);

        platforms.addPlatform( //starting 2
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{250,400}
        );

        platforms.addPlatform( //1st wall
                _data->assets.GetTexture("TestLevel Platform Vertical"),
                sf::Vector2f{600,300}
        );

        platforms.addPlatform( //left platform
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{300,200}
        );

        platforms.addPlatform( //top platform
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{700,100}
        );

        platforms.addPlatform( //long jump
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{1300,400}
        );

        platforms.addPlatform( //with coin
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{1800,600}
        );

        platforms.addPlatform( //above coin
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{1800,200}
        );

        platforms.addPlatform( // dubble jump
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{2800,600}
        );

        _data->assets.LoadTexture("coin", COIN_FILEPATH);
        coin.setTexture(_data->assets.GetTexture("coin"));
        coin.setPosition(1900,590 - coin.getGlobalBounds().height);


        ///Character Initializer
		_data->assets.LoadTexture("TestLevel Character", CHARACTER_FILEPATH);
		_data->assets.LoadTexture("TestLevel Character Flip", CHARACTER_FLIP_FILEPATH);
		character.setPosition(sf::Vector2f {start});
		character.setTexture(_data->assets.GetTexture("TestLevel Character"),_data->assets.GetTexture("TestLevel Character Flip"));
	}

	void TestLevel::HandleInput() {
		character.characterKeyboardInput();
		//std::cout << "Velocity:" << character.velocity.x << ", " << character.velocity.y << std::endl;
		//std::cout << "on_ground:" << character.on_ground << ", jump: " << character.jump << std::endl;

		sf::Event event;

		while(_data->renderWindow.pollEvent(event)){
			if(sf::Event::Closed == event.type){
				_data->renderWindow.close();
			}
			if(sf::Event::LostFocus == event.type){
                _data->machine.AddState( StateRef ( new PauseState(_data)), false);
			}
		}

		//Pause State
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) ||
		    _data->input.IsSpriteClicked(pauseButton, sf::Mouse::Left, _data->renderWindow)){
            _data->machine.AddState( StateRef ( new PauseState(_data)), false);
		}
	}

	void TestLevel::Update(float dt) {
	    ///COIN TEST
	    if(character.getSprite().getGlobalBounds().intersects(coin.getGlobalBounds())){
	        _data->sound._coinSound.play();
	        character.max_jump = 2;
	        coin.setPosition(coin.getPosition().x, 1000);
	    }

	    ///Collision
		bool collision = false;
		for(sf::Sprite platform : platforms.getPlatforms()){
			if(character.objectCollisionAndFalling(platform, dt)){
				collision = true;
			}
		}
		if(!collision){
			character.velocity.y += gravity;
			character.on_ground = false;
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
		    _data->sound._deathSound.play();
			restart();
		}

		//Vie
		cameraX = -(SCREEN_WIDTH/2) + character.getPosition().x;

		//links camera stoppen
		if(cameraX < 0){
			cameraX = 0;
		}
		//rechts camera stoppen
		else if(cameraX > (_background.getPosition().x + _background.getGlobalBounds().width - (SCREEN_WIDTH))){
			cameraX = _background.getPosition().x + _background.getGlobalBounds().width - (SCREEN_WIDTH);
		}

        pauseButton.setPosition(cameraX + SCREEN_WIDTH - 16 - pauseButton.getGlobalBounds().width,16);

		CameraPosition.reset(sf::FloatRect(cameraX, cameraY,  SCREEN_WIDTH, SCREEN_HEIGHT));


	}

	void TestLevel::Draw(float dt) {
		_data->renderWindow.setView(CameraPosition);
		_data->renderWindow.clear();

		//background
		_data->renderWindow.draw(_background);

		//platforms
		platforms.draw();

		//character
		character.draw(_data->renderWindow);

		//coin
		_data->renderWindow.draw(coin);

		//pause
		_data->renderWindow.draw(pauseButton);

		_data->renderWindow.display();
	}

	void TestLevel::restart(){
        character.respawn(start);
        coin.setPosition(1900,590 - coin.getGlobalBounds().height);
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

    void TestLevel::Resume() {
        _data->sound.TestLevelMusic.play();
    }

    void TestLevel::Pause() {
        _data->sound.TestLevelMusic.pause();
    }

}