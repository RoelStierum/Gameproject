#include "SplashState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace engine{

    SplashState::SplashState(GameDataRef data):
        _data(data)
    {}

    void SplashState::Init() {
        _data->assets.LoadTexture("SplashState Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
        _background.setTexture(_data->assets.GetTexture("SplashState Background"));
    }

    void SplashState::HandleInput() {
        sf::Event event;

        while(_data->renderWindow.pollEvent(event)){
            if(sf::Event::Closed == event.type){
                _data->renderWindow.close();
            }
        }
    }

    void SplashState::Update(float dt) {
        if(_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME){
            std::cout << "Go to main menu" << std::endl;
            _data->renderWindow.close();
        }
    }

    void SplashState::Draw(float dt) {
        _data->renderWindow.clear();
        _data->renderWindow.draw(_background);
        _data->renderWindow.display();
    }
}