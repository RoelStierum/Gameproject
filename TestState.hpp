#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <iostream>

namespace engine{

	class TestState: public State{
	public:
		TestState(GameDataRef data):
				_data(data)
		{}

		void Init(){
			_data->assets.LoadTexture("TestState Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
			_background.setTexture(_data->assets.GetTexture("TestState Background"));
			_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

			InitView.reset(sf::FloatRect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
			_data->renderWindow.setView(InitView);
		}

		void HandleInput() {
			sf::Event event;

			while(_data->renderWindow.pollEvent(event)){
				if(sf::Event::Closed == event.type){
					_data->renderWindow.close();
				}
			}
		}

		void Update(float dt) {
			if(_clock.getElapsedTime().asSeconds() > 1){
				_data->machine.RemoveState();
				_data->machine.ProcessStateChanges();
			}
		}

		void Draw(float dt) {
			_data->renderWindow.clear();
			_data->renderWindow.draw(_background);
			_data->renderWindow.display();
		}

	private:
		GameDataRef _data;

		sf::Clock _clock;
		sf::View InitView;

		sf::Texture _backgroundTexture;
		sf::Sprite _background;
	};

}