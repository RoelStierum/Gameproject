#include "TestLevel.hpp"
#include "../PauseState.hpp"
#include "../FinishState.hpp"

#include <iostream>

namespace engine{

	//Constructor for TestLevel
	TestLevel::TestLevel(GameDataRef data):
			_data(data),
			character(data)
	{}

	void TestLevel::Init() {
	    ///START MUSIC
	    _data->sound.BackGroundMusic.play();

	    ///DoubleJump text
	    _data->assets.LoadFont("RussoOneFont", FONT_FILEPATH);
	    doubleJump.setFont(_data->assets.GetFont("RussoOneFont"));
	    doubleJump.setString("Double jump enabled for 10 seconds!");
	    doubleJump.setFillColor(sf::Color::Black);
	    doubleJump.setPosition(1900 -doubleJump.getGlobalBounds().width/2, 400);

        ///DoubleJumpTimerText
        doubleJumpTimeText.setFont(_data->assets.GetFont("RussoOneFont"));
        doubleJumpTimeText.setString("Blank");
        doubleJumpTimeText.setFillColor(sf::Color::Black);

        ///levelTimeTextEnable
        levelTimeText.setFont(_data->assets.GetFont("RussoOneFont"));
        levelTimeText.setString("Blank");
        levelTimeText.setFillColor(sf::Color::Black);


	    ///flag
	    _data->assets.LoadTexture("flag", TESTLEVEL_FLAG_FILEPATH);
        flag.setTexture(_data->assets.GetTexture("flag"));
        flag.setPosition(8060,290);
        //flag.setPosition(400,400); //Debug flag placement


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
		);platforms.addPlatform( //starting 2
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{250,400}
        );platforms.addPlatform( //1st wall
                _data->assets.GetTexture("TestLevel Platform Vertical"),
                sf::Vector2f{600,300}
        );platforms.addPlatform( //left platform
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{300,200}
        );platforms.addPlatform( //top platform
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{700,100}
        );platforms.addPlatform( //long jump
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{1300,400}
        );platforms.addPlatform( //with powerUp
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{1800,600}
        );platforms.addPlatform( //above powerUp
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{1800,200}
        );platforms.addPlatform( // dubble jump
                _data->assets.GetTexture("TestLevel Platform 2"),
                sf::Vector2f{2800,600}
        );platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform 2"),
				sf::Vector2f{3500,500}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform 2"),
				sf::Vector2f{4200,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{4400,300}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{4600,200}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform 2"),
				sf::Vector2f{5000,600}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform 2"),
				sf::Vector2f{5400,530}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform 2"),
				sf::Vector2f{5600,530}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform 2"),
				sf::Vector2f{5530,410}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{5800,500}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform 2"),
				sf::Vector2f{5930,320}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{6350,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{6650,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{6850,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{7050,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{7250,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{7450,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{7650,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{7850,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("TestLevel Platform Vertical"),
				sf::Vector2f{8050,400}
		);


        ///powerUp Initializer
        _data->assets.LoadTexture("powerUp", DOUBLEJUMP_FILEPATH);
        powerUp.setTexture(_data->assets.GetTexture("powerUp"));
        powerUp.setPosition(1900,590 - powerUp.getGlobalBounds().height);


        ///Character Initializer
		_data->assets.LoadTexture("TestLevel Character", CHARACTER_FILEPATH);
		_data->assets.LoadTexture("TestLevel Character Flip", CHARACTER_FLIP_FILEPATH);
		character.setPosition(sf::Vector2f {start});
		character.setTexture(_data->assets.GetTexture("TestLevel Character"),_data->assets.GetTexture("TestLevel Character Flip"));
	    character.velocity.y = 600;
	}

	void TestLevel::HandleInput() {
	    ///Character keyboard input
		if(!finished){
		    character.characterKeyboardInput();
		}
		else{
		    character.velocity = sf::Vector2f(0,0);
		}

		///Window events
		sf::Event event;

		while(_data->renderWindow.pollEvent(event)){
			if(sf::Event::Closed == event.type){
				_data->renderWindow.close();
			}
			if(sf::Event::LostFocus == event.type){
                _data->machine.AddState( StateRef ( new PauseState(_data)), false);
			}
		}

		///Keypress for pause
		//Pause State
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            _data->machine.AddState( StateRef ( new PauseState(_data)), false);
		}

		///Button press for pause
		//Check mouse click on position button
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		    sf::Vector2i m = sf::Mouse::getPosition(_data->renderWindow);
		    sf::IntRect intRect = {SCREEN_WIDTH - 16 - 64,16,64,64};
		    if (m.x >= SCREEN_WIDTH - 16 - 64 && m.x <= SCREEN_WIDTH - 16 && m.y >= 16 && m.y <= 16+64){
                _data->machine.AddState( StateRef ( new PauseState(_data)), false);
		    }
		}
	}

	void TestLevel::Update(float dt) {
	    ///powerUp TEST
	    if(character.getSprite().getGlobalBounds().intersects(powerUp.getGlobalBounds())){
	        _data->sound._coinSound.play();
	        character.max_jump = 2;
	        powerUp.setPosition(powerUp.getPosition().x, 1000);
            doubleJumpEnableText = true;
            doubleJumpTimeTextEnable = true;
			doubleJumpTime.restart();
	    }

	    ///Finish
		if(character.getSprite().getGlobalBounds().intersects(flag.getGlobalBounds()) && !finished){
            _data->sound.BackGroundMusic.stop();
		    _data->sound._winSound.play();
		    clockFinish.restart();
		    finished=true;
            tijd += levelTime.getElapsedTime().asSeconds();
            std::string s = std::to_string(tijd);
            s = s.substr(0,s.size()-4);
            levelTimeText.setString(s);
            std::cout << tijd << std::endl;
		}


		if(clockFinish.getElapsedTime().asSeconds() >= FINISH_TIME && finished){

            _data->machine.AddState( StateRef ( new FinishState(_data, tijd)), true);

		}

        ///DubbleJumpTimer
		if(doubleJumpTime.getElapsedTime().asSeconds() >= DOUBLE_JUMP_TIME){
			character.max_jump = 1;
            doubleJumpTimeTextEnable = false;
            doubleJumpEnableText = false;
		}
		if(doubleJumpTimeTextEnable){
            doubleJumpTimeText.setString(std::to_string(DOUBLE_JUMP_TIME-int(doubleJumpTime.getElapsedTime().asSeconds())));
            doubleJumpTimeText.setPosition(cameraX + SCREEN_WIDTH/2 - doubleJumpTimeText.getGlobalBounds().width/2,10);
        }

		///levelTimeText
		if(!finished){
		    std::string s = std::to_string(levelTime.getElapsedTime().asSeconds() + tijd);
		    s = s.substr(0,s.size()-4);
		    levelTimeText.setString(s);
            levelTimeText.setPosition(SCREEN_WIDTH-100-levelTimeText.getGlobalBounds().width,20);
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


        ///CAMERA VIEW
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

		///Pause button location
        pauseButton.setPosition(cameraX + SCREEN_WIDTH - 16 - pauseButton.getGlobalBounds().width,16);
        ///Text set position
        levelTimeText.setPosition(cameraX + SCREEN_WIDTH-1200-levelTimeText.getGlobalBounds().width,16);

        ///player under screen / respawn
        if (character.getPosition().y > SCREEN_HEIGHT + 100){
            _data->sound._deathSound.play();
            restart();
        }
	}

	void TestLevel::Draw(float dt) {
		_data->renderWindow.setView(CameraPosition);
		_data->renderWindow.clear();

		//background
		_data->renderWindow.draw(_background);

		//platforms
		platforms.draw();

		//powerUp
		_data->renderWindow.draw(powerUp);

		//pause
		_data->renderWindow.draw(pauseButton);

		//doubleJump text
		if(doubleJumpEnableText){
            _data->renderWindow.draw(doubleJump);
		}
		if(doubleJumpTimeTextEnable){
            _data->renderWindow.draw(doubleJumpTimeText);
		}
		_data->renderWindow.draw(levelTimeText);



		//flag
		_data->renderWindow.draw(flag);

        //character
        character.draw(_data->renderWindow);

		_data->renderWindow.display();
	}

	void TestLevel::restart(){
	    doubleJumpEnableText = false;
        doubleJumpTimeTextEnable = false;
        character.respawn(start);
        powerUp.setPosition(1900,590 - powerUp.getGlobalBounds().height);
        levelTime.restart();
        tijd = 0;
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
        _data->sound.BackGroundMusic.play();
        levelTime.restart();
    }

    void TestLevel::Pause() {
	    tijd += levelTime.getElapsedTime().asSeconds();
        _data->sound.BackGroundMusic.pause();
        _data->sound._clickSound.play();
    }

}