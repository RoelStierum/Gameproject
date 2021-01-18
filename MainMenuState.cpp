#include "MainMenuState.hpp"
#include "Levels/TestLevel.hpp"
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
        _play_button.setTexture(_data->assets.GetTexture("MainMenuPlayButton"));
        //_play_button.setScale(2,2);
        _play_button.setPosition(SCREEN_WIDTH/2 + 100, _play_button.getGlobalBounds().height*2.5);

		_data->assets.LoadTexture("MainMenuQuitButton", MAIN_MENU_QUIT_BUTTON_FILEPATH);
		_quit_button.setTexture(_data->assets.GetTexture("MainMenuQuitButton"));
		//_play_button.setScale(2,2);
		_quit_button.setPosition(SCREEN_WIDTH/2 - 100 - _quit_button.getGlobalBounds().width, _quit_button.getGlobalBounds().height*2.5);
    }

    void MainMenuState::HandleInput() {
        sf::Event event;

        while(_data->renderWindow.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                _data->renderWindow.close();
            }
            if(_data->input.IsSpriteClicked(_play_button, sf::Mouse::Left, _data->renderWindow)){
				_data->machine.AddState( StateRef( new TestLevel(_data)), true);
            }
			if(_data->input.IsSpriteClicked(_quit_button, sf::Mouse::Left, _data->renderWindow)){
				_data->renderWindow.close();
			}
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
			_data->machine.AddState( StateRef( new TestLevel(_data)), true);
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
        _data->renderWindow.display();
    }
}