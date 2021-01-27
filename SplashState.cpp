#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace engine{

    //SplashState constructor
    SplashState::SplashState(GameDataRef data):
        _data(data)
    {}

    //Run on initialization of state
    void SplashState::Init() {
        //_background Initializer
        _data->assets.LoadTexture("SplashState Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
        _background.setTexture(_data->assets.GetTexture("SplashState Background"));
        _background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);
    }

    void SplashState::HandleInput() {
        //Window events
        sf::Event event;

        //Check for windows x button
        while(_data->renderWindow.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                _data->renderWindow.close();
            }
        }

        //Check for esc key to skip _clock. Go to MainMenuState
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && _data->renderWindow.hasFocus()){
            _data->machine.AddState( StateRef( new MainMenuState(_data)), true);
        }
    }

    void SplashState::Update(float dt) {
        //If _clock is finished go to MainMenuState
        if(_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
            _data->machine.AddState( StateRef( new MainMenuState(_data)), true);
        }

    }

    void SplashState::Draw(float dt) {
        _data->renderWindow.clear();

        //Draw _background
        _data->renderWindow.draw(_background);

        _data->renderWindow.display();
    }
}