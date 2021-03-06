#include "Level2.hpp"
#include "../PauseState.hpp"
#include "../FinishState.hpp"

#include <iostream>

namespace engine{

    //Constructor for Level2
    Level2::Level2(GameDataRef data):
            _data(data),
            character(data)
    {}

    //Run on initialization of state
    void Level2::Init() {
        //State the background music if not playing
        if(_data->sound.BackGroundMusic.getPlayingOffset().asSeconds() <= 0){
            _data->sound.BackGroundMusic.play();
        }

		//LowGravityText Initializer
		_data->assets.LoadFont("RussoOneFont", FONT_FILEPATH);
		LowGravityText.setFont(_data->assets.GetFont("RussoOneFont"));
		LowGravityText.setString("Low Gravity enabled for 11 seconds!");
		LowGravityText.setFillColor(sf::Color::Black);
		LowGravityText.setPosition(4300 -LowGravityText.getGlobalBounds().width/2, 400);

		//LowGravityTimerText Initializer
		LowGravityTimeText.setFont(_data->assets.GetFont("RussoOneFont"));
		LowGravityTimeText.setString("Blank");
		LowGravityTimeText.setFillColor(sf::Color::Black);

		//levelTimeText Initializer
        _data->assets.LoadFont("RussoOneFont", FONT_FILEPATH);
        levelTimeText.setFont(_data->assets.GetFont("RussoOneFont"));
        levelTimeText.setString("Blank");
        levelTimeText.setFillColor(sf::Color::Black);


        //flag Initializer
        _data->assets.LoadTexture("flag", LEVEL_FLAG_FILEPATH);
        flag.setTexture(_data->assets.GetTexture("flag"));
        flag.setPosition(7900,500-flag.getGlobalBounds().height);
		//flag.setPosition(400,400); //Debug flag placement


		//Background Initializer
        _data->assets.LoadTexture("Level2 Background", LEVEL_BACKGROUND_FILEPATH);
        _background.setTexture(_data->assets.GetTexture("Level2 Background"));
        //_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

        //pauseButton Initializer
        _data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
        pauseButton.setTexture(_data->assets.GetTexture("Pause Button"));
        pauseButton.setPosition(SCREEN_WIDTH-16-pauseButton.getGlobalBounds().width,16);

        //Platform Textures Initializer
        _data->assets.LoadTexture("HorizontalGrassPlatform", PLATFORM_GRASS_FILEPATH);
        _data->assets.LoadTexture("HorizontalGreyPlatform", PLATFORM_GREY_FILEPATH);
        _data->assets.LoadTexture("VerticalGreyPlatform", PLATFORM_GREY_VERTICAL_FILEPATH);
        _data->assets.LoadTexture("VerticalRedForceField", FORCEFIELD_VERTICAL_FILEPATH);

        //Platforms Initializer
        platforms.addPlatform( //starting
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{50,400}
        );platforms.addPlatform( //moving
                _data->assets.GetTexture("HorizontalGrassPlatform"),
                moving_platform_start
        );


        platforms.addPlatform( //wall pre jump
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{900,360}
        );platforms.addPlatform( //wall pre jump
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{1100,300}
        );platforms.addPlatform( //wall before
                _data->assets.GetTexture("VerticalRedForceField"),
                sf::Vector2f{1500,0}
        );platforms.addPlatform( //wall before
                _data->assets.GetTexture("VerticalRedForceField"),
                sf::Vector2f{1500,200}
        );platforms.addPlatform( //wall before
                _data->assets.GetTexture("VerticalRedForceField"),
                sf::Vector2f{1500,400}
        );platforms.addPlatform( //wall pre jump
                _data->assets.GetTexture("HorizontalGrassPlatform"),
                sf::Vector2f{1300,710}
        );platforms.addPlatform( //wall pre jump
                _data->assets.GetTexture("HorizontalGrassPlatform"),
                sf::Vector2f{1500,710}
        );platforms.addPlatform( //wall before
                _data->assets.GetTexture("VerticalGreyPlatform"),
                sf::Vector2f{1800,605}
        );platforms.addPlatform( //wall before
                _data->assets.GetTexture("VerticalGreyPlatform"),
                sf::Vector2f{2050,520}
        );platforms.addPlatform( //wall before
                _data->assets.GetTexture("VerticalGreyPlatform"),
                sf::Vector2f{2300,440}
        );


        platforms.addPlatform( //wall before
                _data->assets.GetTexture("VerticalGreyPlatform"),
                sf::Vector2f{2660,120}
        );platforms.addPlatform( //wall pre jump
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{2700,280}
        );platforms.addPlatform( //wall pre jump
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{3000,360}
        );platforms.addPlatform( //wall
                _data->assets.GetTexture("VerticalGreyPlatform"),
                sf::Vector2f{3100,200}
        );


        platforms.addPlatform( //
                _data->assets.GetTexture("HorizontalGreyPlatform"),
                sf::Vector2f{3700,400}
        );platforms.addPlatform( //
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{4200,500}
		);platforms.addPlatform( //
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{5000,500}
		);platforms.addPlatform( //
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{5800,400}
		);

		platforms.addPlatform( //ceiling
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{6100,-40}
		);
		platforms.addPlatform( //wall
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{6200,200}
		);platforms.addPlatform( //wall
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{6200,400}
		);platforms.addPlatform( //wall
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{6200,600}
		);platforms.addPlatform( //wall
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{6200,800}
		);

		platforms.addPlatform( //wall
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{6300,-200}
		);platforms.addPlatform( //wall
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{6300,0}
		);platforms.addPlatform( //wall
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{6300,200}
		);

		platforms.addPlatform( //
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{6345,630}
		);platforms.addPlatform( //
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{6900,460}
		);platforms.addPlatform( //wall
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{7100,160}
		);
		platforms.addPlatform( //wall
				_data->assets.GetTexture("VerticalGreyPlatform"),
				sf::Vector2f{7100,300}
		);

		platforms.addPlatform( //
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{6450,275}
		);platforms.addPlatform( //
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{6900,160}
		);
		platforms.addPlatform( //
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{7400,400}
		);platforms.addPlatform( //
				_data->assets.GetTexture("HorizontalGreyPlatform"),
				sf::Vector2f{7800,500}
		);



		//lowGravity Initializer
		_data->assets.LoadTexture("lowGravity", LOW_GRAVITY_FILEPATH);
		lowGravity.setTexture(_data->assets.GetTexture("lowGravity"));
		lowGravity.setPosition(4300,490 - lowGravity.getGlobalBounds().height);


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

    void Level2::HandleInput() {
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

    void Level2::Update(float dt) {
       //Start moving platform
        if(move == 0 && character.getPosition().x + character.getSprite().getGlobalBounds().width/2 > 350){
            move = 250; //platform speed
        }

        //Moving platform movement
        sf::Vector2f pos = platforms.getPlatforms()[1].getPosition();
        if((pos.x + platforms.getPlatforms()[1].getGlobalBounds().width >= 3700 && move > 0) || (pos.x < 250 && move < 0)){
            move = move * -1;
        }
        platforms.getPlatforms()[1].setPosition(pos.x+(move*dt),pos.y);

        //Moving platform pushes the character
        if(platforms.getPlatforms()[1].getGlobalBounds().intersects(character.getSprite().getGlobalBounds())){
            if(platforms.getPlatforms()[1].getPosition().x < character.getPosition().x + character.getSprite().getGlobalBounds().width - 1 &&
                platforms.getPlatforms()[1].getPosition().y < character.getPosition().y + character.getSprite().getGlobalBounds().height - 1 &&
                platforms.getPlatforms()[1].getPosition().y + platforms.getPlatforms()[1].getGlobalBounds().height > character.getPosition().y + 1){
                    character.velocity.x = move;
                    character.updateVelocity(dt);
            }
            if(platforms.getPlatforms()[1].getPosition().x + platforms.getPlatforms()[1].getGlobalBounds().width > character.getPosition().x + 1 &&
               platforms.getPlatforms()[1].getPosition().y < character.getPosition().y + character.getSprite().getGlobalBounds().height - 1 &&
               platforms.getPlatforms()[1].getPosition().y + platforms.getPlatforms()[1].getGlobalBounds().height > character.getPosition().y + 1){
                character.velocity.x = move;
                character.updateVelocity(dt);
            }
        }

		//lowGravity Collision with character
		if(character.getSprite().getGlobalBounds().intersects(lowGravity.getGlobalBounds())){
			LowGravityTijd = 0;
			LowGravityTimeEnable = true;
			_data->sound._powerupSound.play();
			gravity = 700;
			lowGravity.setPosition(lowGravity.getPosition().x, 1000);
			LowGravityEnableText = true;
			LowGravityTimeTextEnable = true;
			LowGravityTime.restart();
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

		//If LowGravityTimer is done remove low gravity, the timer and the text
		if(LowGravityTime.getElapsedTime().asSeconds() + LowGravityTijd >= LOW_GRAVITY_TIME && LowGravityTimeEnable){
			gravity = 1500;
			LowGravityTimeTextEnable = false;
			LowGravityEnableText = false;
			LowGravityTimeEnable= false;
		}

		//If LowGravityTimeTextEnable is true: update the timer
		if(LowGravityTimeTextEnable){
			std::string s = std::to_string(LOW_GRAVITY_TIME - (LowGravityTime.getElapsedTime().asSeconds() + LowGravityTijd));
			s = s.substr(0,s.size()-5);
			LowGravityTimeText.setString(s);
			LowGravityTimeText.setPosition(cameraX + SCREEN_WIDTH/2 - LowGravityTimeText.getGlobalBounds().width/2,10);

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

        for(int i = 0; i < platforms.getPlatforms().size(); i++){
            if(i == 4 || i == 5 || i == 6){
                if(character.getSprite().getGlobalBounds().intersects(platforms.getPlatforms()[i].getGlobalBounds())){
                    std::cout << "hit\n";
                    restart();
                    return;
                }
            }else{
                if(character.objectCollisionAndFalling(platforms.getPlatforms()[i], dt)){
                    collision = true;
                }
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
        levelTimeText.setPosition(cameraX + 16, 16);
        //LowGravityTimeText text set position
        if(LowGravityEnableText){
            LowGravityTimeText.setPosition(cameraX + SCREEN_WIDTH/2-32,10);
        }

        //player under screen / respawn
        if (character.getPosition().y > SCREEN_HEIGHT + 100){
            _data->sound._deathSound.play();
            restart();
        }
    }

    void Level2::Draw(float dt) {
        _data->renderWindow.setView(CameraPosition);
        _data->renderWindow.clear();

        //Draw background
        _data->renderWindow.draw(_background);

        //Draw platforms
        platforms.draw();

		//Draw lowGravity
		_data->renderWindow.draw(lowGravity);

        //Draw pauseButton
        _data->renderWindow.draw(pauseButton);

		//Draw LowGravityText
		if(LowGravityEnableText){
			_data->renderWindow.draw(LowGravityText);
		}
		//Draw LowGravityTimeText
		if(LowGravityTimeTextEnable){
			_data->renderWindow.draw(LowGravityTimeText);
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
    void Level2::restart(){
    	gravity = 1500;
		LowGravityEnableText = false;
		LowGravityTimeTextEnable = false;
        character.respawn(start);
		lowGravity.setPosition(4300,490 - lowGravity.getGlobalBounds().height);
		levelTime.restart();
        move = 0;
        platforms.getPlatforms()[1].setPosition(moving_platform_start);
        tijd = 0;
		LowGravityTijd = 0;
	}

    //Check if character is on the edges of the screen and stop the velocity
    void Level2::characterEdgeOfScreen(const Character &character_, const float& dt) {
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
    void Level2::Resume() {
        _data->sound.BackGroundMusic.play();
        levelTime.restart();
		LowGravityTime.restart();
	}

    //Run on pause of state
    void Level2::Pause() {
        tijd += levelTime.getElapsedTime().asSeconds();
		LowGravityTijd += LowGravityTime.getElapsedTime().asSeconds();
		_data->sound.BackGroundMusic.pause();
        _data->sound._clickButtonSound.play();
    }
}