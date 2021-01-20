#include "FinishState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "Levels/TestLevel.hpp"


namespace engine{

	FinishState::FinishState(GameDataRef data):
			_data(data)
	{}

	void FinishState::Init() {
		_data->assets.LoadTexture("FinishState Background", MAIN_MENU_BACKGROUND_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("FinishState Background"));
		_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

		InitView.reset(sf::FloatRect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
		_data->renderWindow.setView(InitView);

		//kan fout gaan als het niet geladen is. moet een bool zijn om te checken of de texture geladen is
		_quit.setTexture(_data->assets.GetTexture("MainMenuQuitButton"));
		_quit.setPosition(SCREEN_WIDTH/2 - _quit.getGlobalBounds().width/2, 200);

		_data->assets.LoadTexture("FinishStatePlayAgainButton", MAIN_MENU_BUTTON_FILEPATH);
		_play_again.setTexture(_data->assets.GetTexture("FinishStatePlayAgainButton"));
		_play_again.setPosition(SCREEN_WIDTH/2 - _play_again.getGlobalBounds().width/2, 350);

		_data->assets.LoadTexture("FinishStateMainMenuButton", PAUSE_MAIN_MENU_BUTTON_FILEPATH);
		_menu.setTexture(_data->assets.GetTexture("FinishStateMainMenuButton"));
		_menu.setPosition(SCREEN_WIDTH/2 - _menu.getGlobalBounds().width/2, 500);
	}

	void FinishState::HandleInput() {
		sf::Event event;

		while(_data->renderWindow.pollEvent(event)){
			if(sf::Event::Closed == event.type){
				_data->renderWindow.close();
			}
		}

		if(_data->input.IsSpriteClicked(_quit, sf::Mouse::Left, _data->renderWindow)){
            _data->sound._clickSound.play();
			_data->renderWindow.close();
		}

		if(_data->input.IsSpriteClicked(_play_again, sf::Mouse::Left, _data->renderWindow)) {
            _data->sound._clickSound.play();
			_data->machine.AddState(StateRef(new TestLevel(_data)), true);
		}

		if(_data->input.IsSpriteClicked(_menu, sf::Mouse::Left, _data->renderWindow)){
            _data->sound._clickSound.play();
			_data->machine.AddState( StateRef( new MainMenuState(_data)), true);
			_data->machine.clean_states();
		}
	}

	void FinishState::Draw(float dt) {
		_data->renderWindow.clear();
		_data->renderWindow.draw(_background);
		_data->renderWindow.draw(_quit);
		_data->renderWindow.draw(_play_again);
		_data->renderWindow.draw(_menu);
		_data->renderWindow.display();
	}
}