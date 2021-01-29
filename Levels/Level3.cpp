#include "Level3.hpp"
#include "../PauseState.hpp"
#include "../FinishState.hpp"

#include <iostream>

namespace engine{

	//Constructor for Level3
	Level3::Level3(GameDataRef data):
			_data(data),
			character(data)
	{}

	//Run on initialization of state
	void Level3::Init() {
		//State the background music if not playing
		if(_data->sound.BackGroundMusic.getPlayingOffset().asSeconds() <= 0){
			_data->sound.BackGroundMusic.play();
		}

		//levelTimeText Initializer
		_data->assets.LoadFont("RussoOneFont", FONT_FILEPATH);
		levelTimeText.setFont(_data->assets.GetFont("RussoOneFont"));
		levelTimeText.setString("Blank");
		levelTimeText.setFillColor(sf::Color::Black);


		//flag Initializer
		_data->assets.LoadTexture("flag", LEVEL_FLAG_FILEPATH);
		flag.setTexture(_data->assets.GetTexture("flag"));
		flag.setPosition(2100,400 -flag.getGlobalBounds().height);


		//Background Initializer
		_data->assets.LoadTexture("Level3 Background", LEVEL_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("Level3 Background"));
		//_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);


		//pauseButton Initializer
		_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
		pauseButton.setTexture(_data->assets.GetTexture("Pause Button"));
		pauseButton.setPosition(SCREEN_WIDTH-16-pauseButton.getGlobalBounds().width,16);


		//Platform Textures Initializer
		_data->assets.LoadTexture("HorizontalGrassPlatform", PLATFORM_GRASS_FILEPATH);
		_data->assets.LoadTexture("HorizontalGreyPlatform", PLATFORM_GREY_FILEPATH);
		_data->assets.LoadTexture("VerticalGreyPlatform", PLATFORM_GREY_VERTICAL_FILEPATH);

		//Platforms Initializer
		platforms.addPlatform( //starting
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{50,400}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{600,500}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{1040,410}
		);platforms.addPlatform(
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{1240,320}
		);platforms.addPlatform(
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{890,210}
		);platforms.addPlatform(
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{1330,120}
		);platforms.addPlatform(
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{1840,500}
		);platforms.addPlatform(//end
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{2030,400}
		);


		//Platforms Initializer
		platforms.addPlatform( //starting
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{50,400}
		);


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

	void Level3::HandleInput() {
		//Character keyboard input
		if(!finished){
			character.characterKeyboardInput();
		}
			//Make character not move when finished.
		else{
			character.velocity = {0,0};
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
			sf::IntRect intRect = {SCREEN_WIDTH - 16 - 64,16,64,64};
			if (m.x >= SCREEN_WIDTH - 16 - 64 && m.x <= SCREEN_WIDTH - 16 && m.y >= 16 && m.y <= 16+64){
				_data->machine.AddState( StateRef ( new PauseState(_data)), false);
			}
		}
	}

	void Level3::Update(float dt) {
		//Finish
		if(character.getSprite().getGlobalBounds().intersects(flag.getGlobalBounds()) && !finished){
			_data->sound.BackGroundMusic.stop();
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
		//levelTimeText set position
		levelTimeText.setPosition(cameraX + 0, 16);

		//player under screen / respawn
		if (character.getPosition().y > SCREEN_HEIGHT + 100){
			_data->sound._deathSound.play();
			restart();
		}
	}

	void Level3::Draw(float dt) {
		_data->renderWindow.setView(CameraPosition);
		_data->renderWindow.clear();

		//Draw background
		_data->renderWindow.draw(_background);

		//Draw platforms
		platforms.draw();

		//Draw pauseButton
		_data->renderWindow.draw(pauseButton);

		//Draw levelTimeText
		_data->renderWindow.draw(levelTimeText);

		//Draw flag
		_data->renderWindow.draw(flag);

		//Draw character
		character.draw(_data->renderWindow);

		_data->renderWindow.display();
	}

	//Function for restarting the level
	void Level3::restart(){
		character.respawn(start);
		levelTime.restart();
		tijd = 0;
	}

	//Check if character is on the edges of the screen and stop the velocity
	void Level3::characterEdgeOfScreen(const Character &character_, const float& dt) {
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
	void Level3::Resume() {
		_data->sound.BackGroundMusic.play();
		levelTime.restart();
	}

	//Run on pause of state
	void Level3::Pause() {
		tijd += levelTime.getElapsedTime().asSeconds();
		_data->sound.BackGroundMusic.pause();
		_data->sound._clickButtonSound.play();
	}

}