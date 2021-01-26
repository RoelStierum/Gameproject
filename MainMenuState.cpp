#include "MainMenuState.hpp"
#include "controlState.hpp"
#include "Levels/TestLevel.hpp"
#include "Levels/Level2.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace engine{

    MainMenuState::MainMenuState(GameDataRef data):
            _data(data)
    {}

    void MainMenuState::Init() {

        _data->assets.LoadTexture("MainMenuState Background", MAIN_MENU_BACKGROUND_FILEPATH);
        _background.setTexture(_data->assets.GetTexture("MainMenuState Background"));
        _background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

        _data->assets.LoadTexture("MainMenuTitle", MAIN_MENU_TITLE_FILEPATH);
        _title.setTexture(_data->assets.GetTexture("MainMenuTitle"));
        //_title.setScale(2,2);
        _title.setPosition(SCREEN_WIDTH/2 - _title.getGlobalBounds().width/2, _title.getGlobalBounds().height/2);

        _data->assets.LoadTexture("MainMenuPlayButton", MAIN_MENU_BUTTON_FILEPATH);
		_data->assets.LoadTexture("MainMenuPlayButtonHover", MAIN_MENU_BUTTON_HOVER_FILEPATH);
        _play_button.setTexture(_data->assets.GetTexture("MainMenuPlayButton"));
        _play_button.setPosition(SCREEN_WIDTH/2 + 100, _play_button.getGlobalBounds().height*2.5);


		_data->assets.LoadTexture("MainMenuQuitButton",MAIN_MENU_QUIT_BUTTON_FILEPATH );
		_data->assets.LoadTexture("MainMenuQuitButtonHover", MAIN_MENU_QUIT_BUTTON_HOVER_FILEPATH);
		_quit_button.setTexture(_data->assets.GetTexture("MainMenuQuitButton"));
		_quit_button.setPosition(SCREEN_WIDTH/2 - 100 - _quit_button.getGlobalBounds().width, _quit_button.getGlobalBounds().height*2.5);


        _data->assets.LoadTexture("MainMenuInstructionsButton", INSTRUCTIONS_BUTTON);
        _data->assets.LoadTexture("MainMenuInstructionsButtonHover", INSTRUCTIONS_BUTTON_HOVER);
        _instructions_button.setTexture(_data->assets.GetTexture("MainMenuInstructionsButton"));
        _instructions_button.setPosition(SCREEN_WIDTH/2 - 220, _instructions_button.getGlobalBounds().height*5.5);
      

		_data->assets.LoadTexture("Unmute", UNMUTE_FILEPATH);
		_data->assets.LoadTexture("Mute", MUTE_FILEPATH);

        if(_data->sound.BackGroundMusic.getVolume() == 0){
            mute = true;
            muteSprite.setTexture(_data->assets.GetTexture("Mute"));
        }else{
            mute = false;
            muteSprite.setTexture(_data->assets.GetTexture("Unmute"));
        }
        muteSprite.setPosition(10,SCREEN_HEIGHT - muteSprite.getGlobalBounds().height - 10);
    }

    void MainMenuState::HandleInput() {
        sf::Event event;

        while(_data->renderWindow.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                _data->renderWindow.close();
            }

			if(_data->input.HoverOverButton(_play_button, _data->renderWindow) && _data->renderWindow.hasFocus() &&!_hoverPlay){
				_hoverPlay = true;
				_play_button.setTexture(_data->assets.GetTexture("MainMenuPlayButtonHover"));
			}
			else if(!_data->input.HoverOverButton(_play_button, _data->renderWindow) && _data->renderWindow.hasFocus() &&_hoverPlay){
				_hoverPlay = false;
				_play_button.setTexture(_data->assets.GetTexture("MainMenuPlayButton"));
			}


			if(_data->input.HoverOverButton(_quit_button, _data->renderWindow) && _data->renderWindow.hasFocus() &&!_hoverQuit){
				_hoverQuit = true;
				_quit_button.setTexture(_data->assets.GetTexture("MainMenuQuitButtonHover"));
			}
			else if(!_data->input.HoverOverButton(_quit_button, _data->renderWindow) && _data->renderWindow.hasFocus() &&_hoverQuit){
				_hoverQuit = false;
				_quit_button.setTexture(_data->assets.GetTexture("MainMenuQuitButton"));
			}

			if(_data->input.HoverOverButton(_instructions_button, _data->renderWindow) && _data->renderWindow.hasFocus() &&!_hoverInstructions){
				_hoverInstructions = true;
				_instructions_button.setTexture(_data->assets.GetTexture("MainMenuInstructionsButtonHover"));
			}
			else if(!_data->input.HoverOverButton(_instructions_button, _data->renderWindow) && _data->renderWindow.hasFocus() &&_hoverInstructions){
				_hoverInstructions = false;
				_instructions_button.setTexture(_data->assets.GetTexture("MainMenuInstructionsButton"));
			}

            if(_data->input.IsSpriteClicked(_play_button, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()){
                _data->sound._clickSound.play();
				_data->machine.AddState( StateRef( new TestLevel(_data)), true);
            }
			if(_data->input.IsSpriteClicked(_quit_button, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()){
                _data->sound._clickSound.play();
				_data->renderWindow.close();
			}
            if(_data->input.IsSpriteClicked(_instructions_button, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()) {
                _data->sound._clickSound.play();
                _data->machine.AddState(StateRef(new ControlState(_data)), true);

            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1) &&
                _data->renderWindow.hasFocus()){
            _data->sound._clickSound.play();
			_data->machine.AddState( StateRef( new TestLevel(_data)), true);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2) &&
           _data->renderWindow.hasFocus()){
            _data->sound._clickSound.play();
            _data->machine.AddState( StateRef( new Level2(_data)), true);
        }

        if(not mouse && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(muteSprite.getGlobalBounds().contains(sf::Vector2f{sf::Mouse::getPosition(_data->renderWindow)})){
                mouse = true;
                if(mute){
                    muteSprite.setTexture(_data->assets.GetTexture("Unmute"));
                    _data->sound.setVolume();
                    mute = false;
                }else{
                    muteSprite.setTexture(_data->assets.GetTexture("Mute"));
                    _data->sound.mute();
                    mute = true;
                }
            }
        }if(mouse && not sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            mouse = false;
        }
    }

    void MainMenuState::Update(float dt) {
        //
    }

    void MainMenuState::Draw(float dt) {
        _data->renderWindow.clear();
        _data->renderWindow.draw(_background);
        _data->renderWindow.draw(_title);
        _data->renderWindow.draw(_play_button);
		_data->renderWindow.draw(_quit_button);
        _data->renderWindow.draw(_instructions_button);
		_data->renderWindow.draw(muteSprite);
        _data->renderWindow.display();
    }
}