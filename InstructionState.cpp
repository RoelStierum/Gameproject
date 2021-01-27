
#include "InstructionState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace engine{

    InstructionState::InstructionState(GameDataRef data):
            _data(data)
    {}

    // init function for loading the images
    void InstructionState::Init() {
        //background image
        _data->assets.LoadTexture("InstructionState Background", MAIN_MENU_BACKGROUND_FILEPATH);
        _background.setTexture(_data->assets.GetTexture("InstructionState Background"));
        _background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);
        //instructions image
        _data->assets.LoadTexture("instructions", INSTRUCTIONS);
        _instructions.setTexture(_data->assets.GetTexture("instructions"));
        _instructions.setPosition(SCREEN_WIDTH/256, _instructions.getGlobalBounds().height - 380);
        //backbutton with hover button
        _data->assets.LoadTexture("BackButton", BACK_BUTTON);
        _data->assets.LoadTexture("BackButtonHover", BACK_BUTTON_HOVER);
        _back.setTexture(_data->assets.GetTexture("BackButton"));
        _back.setPosition(SCREEN_WIDTH/2 - _back.getGlobalBounds().width/2, 500);
    }

    //function for handling mouse inputs in the menu, also provides the hover functionality
    void InstructionState::HandleInput() {
        sf::Event event;

		if(_data->input.HoverOverButton(_back, _data->renderWindow) && _data->renderWindow.hasFocus() &&!_hoverBack){
			_hoverBack = true;
			_back.setTexture(_data->assets.GetTexture("BackButtonHover"));
		}
		else if(!_data->input.HoverOverButton(_back, _data->renderWindow) && _data->renderWindow.hasFocus() &&_hoverBack){
			_hoverBack = false;
			_back.setTexture(_data->assets.GetTexture("BackButton"));
		}

        if(_data->input.IsSpriteClicked(_back, sf::Mouse::Left, _data->renderWindow)&&_data->renderWindow.hasFocus() && !mouseCheck){
            _data->sound._clickButtonSound.play();
            _data->machine.AddState( StateRef( new MainMenuState(_data)), true);
            _data->machine.clean_states();
        }
        if(mouseCheck && not sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        mouseCheck = false;
        }

        while(_data->renderWindow.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                _data->renderWindow.close();
            }
        }

    }

    //function which ables to use the esc key to exit
    void InstructionState::Update(float dt) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            _data->machine.AddState( StateRef( new MainMenuState(_data)), true);
        }
    }

    //draw function for drawing the images.
    void InstructionState::Draw(float dt) {
        _data->renderWindow.clear();
        _data->renderWindow.draw(_background);
        _data->renderWindow.draw(_instructions);
        _data->renderWindow.draw(_back);
        _data->renderWindow.display();
    }
}