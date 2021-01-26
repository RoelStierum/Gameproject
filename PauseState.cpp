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
		_paused.setPosition(SCREEN_WIDTH/2 - _paused.getGlobalBounds().width/2, 0);

		//kan fout gaan als het niet geladen is. moet een bool zijn om te checken of de texture geladen is
		_quit.setTexture(_data->assets.GetTexture("MainMenuQuitButton"));
		_quit.setPosition(SCREEN_WIDTH/2 - _quit.getGlobalBounds().width/2, 200);

        _data->assets.LoadTexture("PauseStateResumeButton", PAUSE_RESUME_BUTTON_FILEPATH);
		_data->assets.LoadTexture("PauseStateResumeButtonHover", PAUSE_RESUME_BUTTON_HOVER_FILEPATH);
		_resume.setTexture(_data->assets.GetTexture("PauseStateResumeButton"));
		_resume.setPosition(SCREEN_WIDTH/2 - _resume.getGlobalBounds().width/2, 350);

        _data->assets.LoadTexture("PauseStateMainMenuButton", PAUSE_MAIN_MENU_BUTTON_FILEPATH);
		_data->assets.LoadTexture("PauseStateMainMenuButtonHover", PAUSE_MAIN_MENU_BUTTON_HOVER_FILEPATH);
		_menu.setTexture(_data->assets.GetTexture("PauseStateMainMenuButton"));
		_menu.setPosition(SCREEN_WIDTH/2 - _menu.getGlobalBounds().width/2, 500);
	}

	void PauseState::HandleInput() {
		sf::Event event;

		while(_data->renderWindow.pollEvent(event)){
			if(sf::Event::Closed == event.type){
				_data->renderWindow.close();
			}
		}


		if(_data->input.HoverOverButton(_quit, _data->renderWindow) && _data->renderWindow.hasFocus() &&!_hoverQuit){
			_hoverQuit = true;
			_quit.setTexture(_data->assets.GetTexture("MainMenuQuitButtonHover"));
		}
		else if(!_data->input.HoverOverButton(_quit, _data->renderWindow) && _data->renderWindow.hasFocus() &&_hoverQuit){
			_hoverQuit = false;
			_quit.setTexture(_data->assets.GetTexture("MainMenuQuitButton"));
		}

		if(_data->input.HoverOverButton(_resume, _data->renderWindow) && _data->renderWindow.hasFocus() &&!_hoverResume){
			_hoverResume = true;
			_resume.setTexture(_data->assets.GetTexture("PauseStateResumeButtonHover"));
		}
		else if(!_data->input.HoverOverButton(_resume, _data->renderWindow) && _data->renderWindow.hasFocus() &&_hoverResume){
			_hoverResume = false;
			_resume.setTexture(_data->assets.GetTexture("PauseStateResumeButton"));
		}

		if(_data->input.HoverOverButton(_menu, _data->renderWindow) && _data->renderWindow.hasFocus() &&!_hoverMainMenu){
			_hoverMainMenu = true;
			_menu.setTexture(_data->assets.GetTexture("PauseStateMainMenuButtonHover"));
		}
		else if(!_data->input.HoverOverButton(_menu, _data->renderWindow) && _data->renderWindow.hasFocus() &&_hoverMainMenu){
			_hoverMainMenu = false;
			_menu.setTexture(_data->assets.GetTexture("PauseStateMainMenuButton"));
		}

		if(_data->input.IsSpriteClicked(_quit, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()){
            _data->sound._clickSound.play();
			_data->renderWindow.close();
		}

		if(_data->input.IsSpriteClicked(_menu, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()){
            _data->sound._clickSound.play();
			_data->machine.AddState( StateRef( new MainMenuState(_data)), true);
			_data->machine.clean_states();
		}

		//if E or sprite press resume
		if((sf::Keyboard::isKeyPressed(sf::Keyboard::E) ||
			_data->input.IsSpriteClicked(_resume, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()) &&
            _data->renderWindow.hasFocus()){
            _data->sound._clickSound.play();
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