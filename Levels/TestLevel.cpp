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

    //Run on initialization of state
    void TestLevel::Init() {
        //State the background music if not playing
	    _data->sound.BackGroundMusic.play();

	    //doubleJumpText Initializer
	    _data->assets.LoadFont("RussoOneFont", FONT_FILEPATH);
	    doubleJumpText.setFont(_data->assets.GetFont("RussoOneFont"));
	    doubleJumpText.setString("Double jump enabled for 10 seconds!");
	    doubleJumpText.setFillColor(sf::Color::Black);
	    doubleJumpText.setPosition(1900 -doubleJumpText.getGlobalBounds().width/2, 400);

        //DoubleJumpTimerText Initializer
        doubleJumpTimeText.setFont(_data->assets.GetFont("RussoOneFont"));
        doubleJumpTimeText.setString("Blank");
        doubleJumpTimeText.setFillColor(sf::Color::Black);

        //levelTimeText Initializer
        levelTimeText.setFont(_data->assets.GetFont("RussoOneFont"));
        levelTimeText.setString("Blank");
        levelTimeText.setFillColor(sf::Color::Black);


	    //flagInitializer
	    _data->assets.LoadTexture("flag", TESTLEVEL_FLAG_FILEPATH);
        flag.setTexture(_data->assets.GetTexture("flag"));
        flag.setPosition(10060,270);
        //flag.setPosition(400,400); //Debug flag placement


        //pauseButton Initializer
		_data->assets.LoadTexture("TestLevel Background", LEVEL_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("TestLevel Background"));
		//_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);
        //_background.setPosition(0,2);


		//Pause button
		_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
		pauseButton.setTexture(_data->assets.GetTexture("Pause Button"));
		pauseButton.setPosition(SCREEN_WIDTH-16-pauseButton.getGlobalBounds().width,16);


        //Platform Textures Initializer
		_data->assets.LoadTexture("HorizontalGrassPlatform", PLATFORM_GRASS_FILEPATH);
		_data->assets.LoadTexture("HorizontalGreyPlatform", PLATFORM_GREY_FILEPATH);
        _data->assets.LoadTexture("HorizontalGrassPlatformVertical", PLATFORM_GREY_VERTICAL_FILEPATH);

        //Platforms Initializer
		platforms.addPlatform( //starting
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{50,400}
		);platforms.addPlatform( //starting 2
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{250,400}
        );platforms.addPlatform( //1st wall
                _data->assets.GetTexture("HorizontalGrassPlatformVertical"),
                sf::Vector2f{600,300}
        );platforms.addPlatform( //left platform
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{300,200}
        );platforms.addPlatform( //top platform
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{700,100}
        );platforms.addPlatform( //long jump
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{1300,400}
        );platforms.addPlatform( //with powerUp
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{1800,600}
        );platforms.addPlatform( //above powerUp
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{1800,200}
        );platforms.addPlatform( // dubble jump
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{2800,600}
        );platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{3500,500}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{4200,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{4400,300}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{4600,200}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{5000,600}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{5400,530}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{5600,530}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{5530,410}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{5800,500}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{5930,320}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{6350,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{6650,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{6850,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{7050,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{7250,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{7450,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{7650,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{7850,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{8050,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{8250,292}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{8250,180}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{8650,600}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{9080,550}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{9350,450}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{9700,380}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGrassPlatformVertical"),
				sf::Vector2f{10050,380}
		);


        //powerUp Initializer
        _data->assets.LoadTexture("powerUp", DOUBLEJUMP_FILEPATH);
        powerUp.setTexture(_data->assets.GetTexture("powerUp"));
        powerUp.setPosition(1900,590 - powerUp.getGlobalBounds().height);


        //Character Initializer
		_data->assets.LoadTexture("Character", CHARACTER_FILEPATH);
		_data->assets.LoadTexture("Character Flip", CHARACTER_FLIP_FILEPATH);
		_data->assets.LoadTexture("Character right1", CHARACTER_RUN_RIGHT_FILEPATH);
		_data->assets.LoadTexture("Character right2", CHARACTER_RUN_RIGHT2_FILEPATH);
		_data->assets.LoadTexture("Character left1", CHARACTER_RUN_LEFT_FILEPATH);
		_data->assets.LoadTexture("Character left2", CHARACTER_RUN_LEFT2_FILEPATH);
		character.setPosition(sf::Vector2f {start});
		character.setTexture(
		        _data->assets.GetTexture("Character"),
		        _data->assets.GetTexture("Character Flip"),
		        _data->assets.GetTexture("Character right1"),
		        _data->assets.GetTexture("Character right2"),
		        _data->assets.GetTexture("Character left1"),
		        _data->assets.GetTexture("Character left2")
		        );
	    character.velocity.y = 600;
	}

	void TestLevel::HandleInput() {
	    //Character keyboard input
		if(!finished){
		    character.characterKeyboardInput();
		}
		else{
		    character.velocity = sf::Vector2f(0,0);
		}

		//Window events
		sf::Event event;

		while(_data->renderWindow.pollEvent(event)){

            //Check for windows x button
            if(sf::Event::Closed == event.type){
				_data->renderWindow.close();
			}

            //Check for lost focus of window
			if(sf::Event::LostFocus == event.type){
                _data->machine.AddState( StateRef ( new PauseState(_data)), false);
			}
		}

		//Keypress for pause
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            _data->machine.AddState( StateRef ( new PauseState(_data)), false);
		}

        //Button press for pause and check mouse click on position button
		if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		    sf::Vector2i m = sf::Mouse::getPosition(_data->renderWindow);
		    //sf::IntRect intRect = {SCREEN_WIDTH - 16 - 64,16,64,64};
		    if (m.x >= SCREEN_WIDTH - 16 - 64 && m.x <= SCREEN_WIDTH - 16 && m.y >= 16 && m.y <= 16+64){
                _data->machine.AddState( StateRef ( new PauseState(_data)), false);
		    }
		}
	}

	void TestLevel::Update(float dt) {
	    //powerUp Collision with character
	    if(character.getSprite().getGlobalBounds().intersects(powerUp.getGlobalBounds())){
            doubleJumpTimeEnable = true;
	        _data->sound._powerupSound.play();
	        character.max_jump = 2;
	        powerUp.setPosition(powerUp.getPosition().x, 1000);
            doubleJumpEnableText = true;
            doubleJumpTimeTextEnable = true;
			doubleJumpTime.restart();
	    }

	    //Finish
		if(character.getSprite().getGlobalBounds().intersects(flag.getGlobalBounds()) && !finished){
        //_data->sound.BackGroundMusic.stop();
		    _data->sound._flagSound.play();
		    clockFinish.restart();
		    finished=true;
            tijd += levelTime.getElapsedTime().asSeconds();
            std::string s = std::to_string(tijd);
            s = s.substr(0,s.size()-4);
            levelTimeText.setString(s);
		}

        //If clockFinish is done go to finish state
		if(clockFinish.getElapsedTime().asSeconds() >= FINISH_FLAG_WAIT && finished){
            _data->machine.AddState( StateRef ( new FinishState(_data, tijd, levelNumber)), true);
		}

        //If DoubleJumpTimer is done remove double jump, the timer and the text
		if(doubleJumpTime.getElapsedTime().asSeconds() + doubleJumpTijd >= DOUBLE_JUMP_TIME && doubleJumpTimeEnable){
			character.max_jump = 1;
            doubleJumpTimeTextEnable = false;
            doubleJumpEnableText = false;
            doubleJumpTimeEnable= false;
		}

        //If doubleJumpTimeTextEnable is true: update the timer
		if(doubleJumpTimeTextEnable){
            std::string s = std::to_string(DOUBLE_JUMP_TIME - (doubleJumpTime.getElapsedTime().asSeconds() + doubleJumpTijd));
            s = s.substr(0,s.size()-5);
            doubleJumpTimeText.setString(s);
            doubleJumpTimeText.setPosition(cameraX + SCREEN_WIDTH/2 - doubleJumpTimeText.getGlobalBounds().width/2,10);
        }

        //If the game is not finished: update the timer
		if(!finished){
		    std::string s = std::to_string(levelTime.getElapsedTime().asSeconds() + tijd);
		    s = s.substr(0,s.size()-4);
		    levelTimeText.setString(s);
            levelTimeText.setPosition(SCREEN_WIDTH-100-levelTimeText.getGlobalBounds().width,20);
		}

		//Character update
		character.update();

        //Collision with platforms and if not make the character fall with the gravity
		bool collision = false;
		for(sf::Sprite platform : platforms.getPlatforms()){
			if(character.objectCollisionAndFalling(platform, dt)){
				collision = true;
			}
		}
		if(!collision){
			character.velocity.y += gravity * dt;
			character.on_ground = false;
			character.slow_down = character.slow_down_air;
			character.speed_up = character.speed_up_air;
		}else{
			character.slow_down = character.slow_down_ground;
			character.speed_up = character.speed_up_ground;
		}

        //Check if character is on the edges of the screen and stop the velocity
        characterEdgeOfScreen(character, dt);

        //Update the character position based on the velocity
        character.updateVelocity(dt);


        //CAMERA VIEW
		cameraX = -(SCREEN_WIDTH/2) + character.getPosition().x;

        //Stop the camera from scrolling to the left of the background
		if(cameraX < 0){
			cameraX = 0;
		}
        //Stop the camera from scrolling to the right of the background
		else if(cameraX > (_background.getPosition().x + _background.getGlobalBounds().width - (SCREEN_WIDTH))){
			cameraX = _background.getPosition().x + _background.getGlobalBounds().width - (SCREEN_WIDTH);
		}

        //Set the camera position
        CameraPosition.reset(sf::FloatRect(cameraX, cameraY,  SCREEN_WIDTH, SCREEN_HEIGHT));

		//Pause button location
        pauseButton.setPosition(cameraX + SCREEN_WIDTH - 16 - pauseButton.getGlobalBounds().width,16);
        //leveltime text set position
        levelTimeText.setPosition(cameraX + SCREEN_WIDTH-1200-levelTimeText.getGlobalBounds().width,16);
        //Double jump timer set position
        doubleJumpTimeText.setPosition(cameraX + SCREEN_WIDTH-640-doubleJumpTimeText.getGlobalBounds().width,16);

        //player under screen / respawn
        if (character.getPosition().y > SCREEN_HEIGHT + 100){
            _data->sound._deathSound.play();
            restart();
        }
	}

    void TestLevel::Draw(float dt) {
		_data->renderWindow.setView(CameraPosition);
		_data->renderWindow.clear();

        //Draw background
		_data->renderWindow.draw(_background);

        //Draw platforms
		platforms.draw();

		//Draw powerUp
		_data->renderWindow.draw(powerUp);

        //Draw pauseButton
		_data->renderWindow.draw(pauseButton);

		//Draw doubleJumpText
		if(doubleJumpEnableText){
            _data->renderWindow.draw(doubleJumpText);
		}
		//Draw doubleJumpTimeText
		if(doubleJumpTimeTextEnable){
            _data->renderWindow.draw(doubleJumpTimeText);
		}

        //Draw levelTimeText
        _data->renderWindow.draw(levelTimeText);

        //Draw flag
		_data->renderWindow.draw(flag);

        //Draw character
        character.draw(_data->renderWindow);

		_data->renderWindow.display();
	}

    //Function for restarting the level
    void TestLevel::restart(){
	    doubleJumpEnableText = false;
        doubleJumpTimeTextEnable = false;
        character.respawn(start);
        powerUp.setPosition(1900,590 - powerUp.getGlobalBounds().height);
        levelTime.restart();
        tijd = 0;
        doubleJumpTijd = 0;
	}

    //Check if character is on the edges of the screen and stop the velocity
    void TestLevel::characterEdgeOfScreen(const Character &character_, const float& dt) {
		//left
		if(character.nextPosition(character.velocity * dt).x < _background.getPosition().x){
			character.velocity.x = 0;
		}
		//right
		if(character.nextPosition(character.velocity * dt).x + character.getSprite().getGlobalBounds().width > _background.getPosition().x + _background.getGlobalBounds().width){
			character.velocity.x = 0;
		}
	}

    //Run on resume of state
    void TestLevel::Resume() {
        _data->sound.BackGroundMusic.play();
        levelTime.restart();
        doubleJumpTime.restart();
    }

    //Run on pause of state
    void TestLevel::Pause() {
	    tijd += levelTime.getElapsedTime().asSeconds();
	    doubleJumpTijd += doubleJumpTime.getElapsedTime().asSeconds();
        _data->sound.BackGroundMusic.pause();
        _data->sound._clickButtonSound.play();
    }

}