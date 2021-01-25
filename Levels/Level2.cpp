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

    void Level2::Init() {
        character.max_jump = 1000;

        ///START MUSIC
        _data->sound.BackGroundMusic.play();

        ///levelTimeTextEnable
        _data->assets.LoadFont("RussoOneFont", FONT_FILEPATH);
        levelTimeText.setFont(_data->assets.GetFont("RussoOneFont"));
        levelTimeText.setString("Blank");
        levelTimeText.setFillColor(sf::Color::Black);

        ///flag
        _data->assets.LoadTexture("flag", TESTLEVEL_FLAG_FILEPATH);
        flag.setTexture(_data->assets.GetTexture("flag"));
        flag.setPosition(8060,290);
        flag.setPosition(400,400); //Debug flag placement

        ///Background Initializer
        _data->assets.LoadTexture("Level2 Background", TESTLEVEL_BACKGROUND_FILEPATH);
        _background.setTexture(_data->assets.GetTexture("Level2 Background"));
        //_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

        ///Pause button
        _data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
        pauseButton.setTexture(_data->assets.GetTexture("Pause Button"));
        pauseButton.setPosition(SCREEN_WIDTH-16-pauseButton.getGlobalBounds().width,16);

        ///Platforms Texture Initializer
        _data->assets.LoadTexture("Level2 Platform", TESTLEVEL_PLATFORM_FILEPATH);
        _data->assets.LoadTexture("Level2 Platform 2", TESTLEVEL_PLATFORM2_FILEPATH);
        _data->assets.LoadTexture("Level2 Platform Vertical", TESTLEVEL_PLATFORM_VERTICAL_FILEPATH);

        ///Platforms Initializer
        platforms.addPlatform( //starting
                _data->assets.GetTexture("Level2 Platform 2"),
                sf::Vector2f{50,400}
        );
        platforms.addPlatform( //starting
                _data->assets.GetTexture("Level2 Platform 2"),
                sf::Vector2f{250,400}
        );

        ///Character Initializer
        _data->assets.LoadTexture("Level2 Character", CHARACTER_FILEPATH);
        _data->assets.LoadTexture("Level2 Character Flip", CHARACTER_FLIP_FILEPATH);
        _data->assets.LoadTexture("Level2 Character right1", CHARACTER_RUN_RIGHT_FILEPATH);
        _data->assets.LoadTexture("Level2 Character right2", CHARACTER_RUN_RIGHT2_FILEPATH);
        _data->assets.LoadTexture("Level2 Character left1", CHARACTER_RUN_LEFT_FILEPATH);
        _data->assets.LoadTexture("Level2 Character left2", CHARACTER_RUN_LEFT2_FILEPATH);
        character.setPosition(sf::Vector2f {start});
        character.setTexture(
                _data->assets.GetTexture("Level2 Character"),
                _data->assets.GetTexture("Level2 Character Flip"),
                _data->assets.GetTexture("Level2 Character right1"),
                _data->assets.GetTexture("Level2 Character right2"),
                _data->assets.GetTexture("Level2 Character left1"),
                _data->assets.GetTexture("Level2 Character left2")
        );
        character.velocity.y = 600;
    }

    void Level2::HandleInput() {
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

    void Level2::Update(float dt) {
        ///TEST
        sf::Vector2f pos = platforms.getPlatforms()[1].getPosition();
        platforms.getPlatforms()[1].setPosition(pos.x+(100*dt),pos.y);


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

            _data->machine.AddState( StateRef ( new FinishState(_data, tijd, levelNumber)), true);

        }

        ///levelTimeText
        if(!finished){
            std::string s = std::to_string(levelTime.getElapsedTime().asSeconds() + tijd);
            s = s.substr(0,s.size()-4);
            levelTimeText.setString(s);
            levelTimeText.setPosition(SCREEN_WIDTH-100-levelTimeText.getGlobalBounds().width,20);
        }

        ///Character
        character.update();

        ///Collision
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
        ///leveltime text set position
        levelTimeText.setPosition(cameraX + SCREEN_WIDTH-1200-levelTimeText.getGlobalBounds().width,16);

        ///player under screen / respawn
        if (character.getPosition().y > SCREEN_HEIGHT + 100){
            _data->sound._deathSound.play();
            restart();
        }
    }

    void Level2::Draw(float dt) {
        _data->renderWindow.setView(CameraPosition);
        _data->renderWindow.clear();

        //background
        _data->renderWindow.draw(_background);

        //platforms
        platforms.draw();

        //pause
        _data->renderWindow.draw(pauseButton);

        _data->renderWindow.draw(levelTimeText);



        //flag
        _data->renderWindow.draw(flag);

        //character
        character.draw(_data->renderWindow);

        _data->renderWindow.display();
    }

    void Level2::restart(){
        character.respawn(start);
        levelTime.restart();
        tijd = 0;
    }

    void Level2::characterEndgeOfScreen(const Character &character_, const float& dt) {
        //links
        if(character.nextPosition(character.velocity * dt).x < _background.getPosition().x){
            character.velocity.x = 0;
        }
        //rechts
        if(character.nextPosition(character.velocity * dt).x + character.width > _background.getPosition().x + _background.getGlobalBounds().width){
            character.velocity.x = 0;
        }
    }

    void Level2::Resume() {
        _data->sound.BackGroundMusic.play();
        levelTime.restart();
    }

    void Level2::Pause() {
        tijd += levelTime.getElapsedTime().asSeconds();
        _data->sound.BackGroundMusic.pause();
        _data->sound._clickSound.play();
    }

}