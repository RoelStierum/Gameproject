#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include <iostream>

namespace engine{

	class PauseState: public State{
	public:
		PauseState(GameDataRef data):
				_data(data)
		{}

		void Init(){
			_data->assets.LoadTexture("PauseState Background", PAUSE_BACKGROUND_FILEPATH);
			_background.setTexture(_data->assets.GetTexture("PauseState Background"));
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

			if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
				_data->machine.RemoveState();
				_data->machine.ProcessStateChanges();
			}
		}

		void Update(float dt) {
		}

		void Draw(float dt) {
			_data->renderWindow.clear();
			_data->renderWindow.draw(_background);
			_data->renderWindow.draw(_paused);
			_data->renderWindow.display();
		}

	private:
		GameDataRef _data;

		sf::View InitView;

		sf::Sprite _background;

		sf::Sprite _paused;
	};

}