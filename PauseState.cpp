#include "PauseState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"

namespace engine{

	PauseState::PauseState(GameDataRef data):
			_data(data)
	{}

	void PauseState::Init() {
		_data->assets.LoadTexture("PauseState Background", PAUSE_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("PauseState Background"));
		_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

		InitView.reset(sf::FloatRect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
		_data->renderWindow.setView(InitView);

		_data->assets.LoadTexture("PauseState Paused", PAUSE_PAUSED_BUTTON_FILEPATH);
		_paused.setTexture(_data->assets.GetTexture("PauseState Paused"));
		_paused.setPosition(SCREEN_WIDTH/2 - _paused.getGlobalBounds().width/2, _paused.getGlobalBounds().height/2);

		//kan fout gaan als het niet geladen is. moet een bool zijn om te checken of de texture geladen is
		_quit.setTexture(_data->assets.GetTexture("MainMenuQuitButton"));
		_quit.setPosition(SCREEN_WIDTH/2 - _quit.getGlobalBounds().width/2, _paused.getGlobalBounds().height*2);

		_resume.setTexture(_data->assets.GetTexture("MainMenuPlayButton"));
		_resume.setPosition(SCREEN_WIDTH/2 - _resume.getGlobalBounds().width/2, _resume.getGlobalBounds().height*3);

		_menu.setTexture(_data->assets.GetTexture("MainMenuPlayButton"));
		_menu.setPosition(SCREEN_WIDTH/2 - _menu.getGlobalBounds().width/2, _menu.getGlobalBounds().height*4);
	}

	void PauseState::HandleInput() {
		sf::Event event;

		while(_data->renderWindow.pollEvent(event)){
			if(sf::Event::Closed == event.type){
				_data->renderWindow.close();
			}
		}

		if(_data->input.IsSpriteClicked(_quit, sf::Mouse::Left, _data->renderWindow)){
			_data->renderWindow.close();
		}

		if(_data->input.IsSpriteClicked(_menu, sf::Mouse::Left, _data->renderWindow)){
			_data->machine.AddState( StateRef( new MainMenuState(_data)), true);
			_data->machine.clean_states();
		}

		//if E or sprite press resume
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::E) ||
			_data->input.IsSpriteClicked(_resume, sf::Mouse::Left, _data->renderWindow)) &&
            _data->renderWindow.hasFocus()){
			_data->machine.RemoveState();
			_data->machine.ProcessStateChanges();
		}
	}

	void PauseState::Draw(float dt) {
		_data->renderWindow.clear();
		_data->renderWindow.draw(_background);
		_data->renderWindow.draw(_paused);
		_data->renderWindow.draw(_quit);
		_data->renderWindow.draw(_resume);
		_data->renderWindow.draw(_menu);
		_data->renderWindow.display();
	}
}