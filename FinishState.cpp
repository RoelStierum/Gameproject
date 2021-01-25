#include "FinishState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "Levels/TestLevel.hpp"
#include "Levels/Level2.hpp"

#include <fstream>


namespace engine{

	FinishState::FinishState(GameDataRef data, const float& tijd, const int& levelNumber):
			_data(data),
			tijd(tijd),
            lastLevel(levelNumber)
	{}

	void FinishState::Init() {
		if (lastLevel == 1){
			std::ifstream readFile1;
			readFile1.open("Audio/Highscore1.txt");
			if (readFile1.is_open()){
				while (!readFile1.eof()){
					readFile1 >> _bestTime;
				}
			}
			readFile1.close();

			std::ofstream writeFile1;
			writeFile1.open("Audio/Highscore1.txt");
			if (writeFile1.is_open()){
				if (tijd < _bestTime){
					_bestTime = tijd;
				}
				writeFile1 << _bestTime;
			}
			writeFile1.close();
		}

		else if (lastLevel == 2){
			std::ifstream readFile2;
			readFile2.open("Audio/Highscore2.txt");
			if (readFile2.is_open()){
				while (!readFile2.eof()){
					readFile2 >> _bestTime;
				}
			}
			readFile2.close();

			std::ofstream writeFile2;
			writeFile2.open("Audio/Highscore2.txt");
			if (writeFile2.is_open()){
				if (tijd < _bestTime){
					_bestTime = tijd;
				}
				writeFile2 << _bestTime;
			}
			writeFile2.close();
		}

		_data->assets.LoadTexture("FinishState Background", BACKGROUND_FINISH_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("FinishState Background"));
		_background.setScale(SCREEN_WIDTH/_background.getGlobalBounds().width,SCREEN_HEIGHT/_background.getGlobalBounds().height);

		InitView.reset(sf::FloatRect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
		_data->renderWindow.setView(InitView);

		_data->assets.LoadTexture("FinishStatePlayAgainButton", END_NEXT_LEVEL_BUTTON_FILEPATH);
		_play_next_level.setTexture(_data->assets.GetTexture("FinishStatePlayAgainButton"));
		_play_next_level.setPosition(SCREEN_WIDTH/2 - _play_next_level.getGlobalBounds().width/2, 200);

		_data->assets.LoadTexture("FinishStateMainMenuButton", PAUSE_MAIN_MENU_BUTTON_FILEPATH);
		_menu.setTexture(_data->assets.GetTexture("FinishStateMainMenuButton"));
		_menu.setPosition(SCREEN_WIDTH/2 - _menu.getGlobalBounds().width/2, 350);

        //kan fout gaan als het niet geladen is. moet een bool zijn om te checken of de texture geladen is
        _quit.setTexture(_data->assets.GetTexture("MainMenuQuitButton"));
        _quit.setPosition(SCREEN_WIDTH/2 - _quit.getGlobalBounds().width/2, 500);

        ///levelTimeTextEnable
        tijdText.setFont(_data->assets.GetFont("RussoOneFont"));
        tijdText.setFillColor(sf::Color::Black);
        tijdText.setCharacterSize(90);
        std::string time = std::to_string(tijd);
		time = time.substr(0,time.size()-4);
        tijdText.setString("Your time: " +time);
        tijdText.setPosition(SCREEN_WIDTH/2 - tijdText.getGlobalBounds().width/2 - 10, 10);

		///levelBestTime
		bestTimeText.setFont(_data->assets.GetFont("RussoOneFont"));
		bestTimeText.setFillColor(sf::Color::Black);
		bestTimeText.setCharacterSize(90);
		std::string bestTime = std::to_string(_bestTime);
		bestTime = bestTime.substr(0,bestTime.size()-4);
		bestTimeText.setString("Best time: " +bestTime);
		bestTimeText.setPosition(SCREEN_WIDTH/2 - tijdText.getGlobalBounds().width/2 - 10, 100);
	}

	void FinishState::HandleInput() {
		sf::Event event;

		while(_data->renderWindow.pollEvent(event)){
			if(sf::Event::Closed == event.type){
				_data->renderWindow.close();
			}
		}

        if(_data->input.IsSpriteClicked(_play_next_level, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()) {
            if(lastLevel == 1){
                _data->sound._clickSound.play();
                _data->machine.AddState(StateRef(new Level2(_data)), true);
            }
        }

        if(_data->input.IsSpriteClicked(_menu, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()){
            _data->sound._clickSound.play();
            _data->machine.AddState( StateRef( new MainMenuState(_data)), true);
            _data->machine.clean_states();
        }

		if(_data->input.IsSpriteClicked(_quit, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()){
            _data->sound._clickSound.play();
			_data->renderWindow.close();
		}
	}

	void FinishState::Draw(float dt) {
		_data->renderWindow.clear();
		_data->renderWindow.draw(_background);
		_data->renderWindow.draw(_quit);
		if(lastLevel < LEVEL_AMOUNT){
            _data->renderWindow.draw(_play_next_level);
		}
		_data->renderWindow.draw(_menu);
		_data->renderWindow.draw(tijdText);
		_data->renderWindow.draw(bestTimeText);
		_data->renderWindow.display();
	}
}