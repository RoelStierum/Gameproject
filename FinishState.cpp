#include "FinishState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "Levels/TestLevel.hpp"
#include "Levels/Level2.hpp"

#include <fstream>


namespace engine{

    //Constructor of FinishState
	FinishState::FinishState(GameDataRef data, const float& tijd, const int& levelNumber):
			_data(data),
			tijd(tijd),
            lastLevel(levelNumber)
	{}

	void FinishState::Init() {
        //background Initializer
		_data->assets.LoadTexture("FinishState Background", BACKGROUND_FINISH_FILEPATH);
		_background.setTexture(_data->assets.GetTexture("FinishState Background"));
		_background.setScale(SCREEN_WIDTH / _background.getGlobalBounds().width,
							 SCREEN_HEIGHT / _background.getGlobalBounds().height);

		InitView.reset(sf::FloatRect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
		_data->renderWindow.setView(InitView);

        //play_next button Initializer
		_data->assets.LoadTexture("FinishStateNextLevelButton", END_NEXT_LEVEL_BUTTON_FILEPATH);
		_data->assets.LoadTexture("FinishStateNextLevelButtonHover", END_NEXT_LEVEL_BUTTON_HOVER_FILEPATH);
		_play_next_level.setTexture(_data->assets.GetTexture("FinishStateNextLevelButton"));
		_play_next_level.setPosition(SCREEN_WIDTH / 2 - _play_next_level.getGlobalBounds().width / 2, 200);

        //menu button Initializer
		_data->assets.LoadTexture("FinishStateMainMenuButton", FINISH_MAIN_MENU_BUTTON_FILEPATH);
		_data->assets.LoadTexture("FinishStateMainMenuButtonHover", FINISH_MAIN_MENU_BUTTON_HOVER_FILEPATH);
		_menu.setTexture(_data->assets.GetTexture("FinishStateMainMenuButton"));
		_menu.setPosition(SCREEN_WIDTH / 2 - _menu.getGlobalBounds().width / 2, 350);

        //quit button Initializer
		_data->assets.LoadTexture("FinishStateQuitButton", FINISH_QUIT_BUTTON_FILEPATH);
		_data->assets.LoadTexture("FinishStateQuitButtonHover", FINISH_QUIT_BUTTON_HOVER_FILEPATH);
		_quit.setTexture(_data->assets.GetTexture("MainMenuQuitButton"));
		_quit.setPosition(SCREEN_WIDTH / 2 - _quit.getGlobalBounds().width / 2, 500);

        //tijdText Initializer
        tijdText.setFont(_data->assets.GetFont("RussoOneFont"));
        tijdText.setFillColor(sf::Color::Black);
        tijdText.setCharacterSize(90);

        //bestTimeText Initializer
        bestTimeText.setFont(_data->assets.GetFont("RussoOneFont"));
        bestTimeText.setFillColor(sf::Color::Black);
        bestTimeText.setCharacterSize(90);

		//Make string for high score filename
		std::string file = HIGHSCORE_FILENAME;
		file += std::to_string(lastLevel);
		file += ".txt";

		//Read high score file
		std::ifstream readFile;
		readFile.open(file);
		if (readFile.is_open()) {
			while (!readFile.eof()) {
				readFile >> _bestTime;
			}
		}
		readFile.close();

		//Write file
		if (tijd < _bestTime) {
		    
			//tijdText
			std::string time = std::to_string(tijd);
			time = time.substr(0, time.size() - 4);
			tijdText.setString("New best Time! " + time);
            tijdText.setPosition(SCREEN_WIDTH / 2 - tijdText.getGlobalBounds().width / 2 - 10, 10);

            //bestTimeText
			std::string bestTime = std::to_string(_bestTime);
			bestTime = bestTime.substr(0, bestTime.size() - 4);
			bestTimeText.setString("Previous best time: " + bestTime);
            bestTimeText.setPosition(SCREEN_WIDTH / 2 - tijdText.getGlobalBounds().width / 2 - 90, 100);

            //Update _bestTime and write to file
            _bestTime = tijd;
			std::ofstream writeFile;
			writeFile.open(file);
			if (writeFile.is_open()) {
				writeFile << _bestTime;
			}
			writeFile.close();
			
		} else {
		    
			//tijdText update string and position
			std::string time = std::to_string(tijd);
			time = time.substr(0, time.size() - 4);
			tijdText.setString("Your time: " + time);
			tijdText.setPosition(SCREEN_WIDTH / 2 - tijdText.getGlobalBounds().width / 2 - 10, 10);

			//bestTimeText update string and position
			std::string bestTime = std::to_string(_bestTime);
			bestTime = bestTime.substr(0, bestTime.size() - 4);
			bestTimeText.setString("Best time: " + bestTime);
			bestTimeText.setPosition(SCREEN_WIDTH / 2 - tijdText.getGlobalBounds().width / 2 - 10, 100);
			
		}
	}

	void FinishState::HandleInput() {
		sf::Event event;

		//Check for windows x button
		while(_data->renderWindow.pollEvent(event)){
			if(sf::Event::Closed == event.type){
				_data->renderWindow.close();
			}
		}

		//Change texture if hovered over quit button
		if(_data->input.HoverOverButton(_quit, _data->renderWindow) && _data->renderWindow.hasFocus() &&!_hoverQuit){
			_hoverQuit = true;
			_quit.setTexture(_data->assets.GetTexture("FinishStateQuitButtonHover"));
		}
		else if(!_data->input.HoverOverButton(_quit, _data->renderWindow) && _data->renderWindow.hasFocus() &&_hoverQuit){
			_hoverQuit = false;
			_quit.setTexture(_data->assets.GetTexture("FinishStateQuitButton"));
		}

        //Change texture if hovered over play_next button
		if(_data->input.HoverOverButton(_play_next_level, _data->renderWindow) && _data->renderWindow.hasFocus() &&!_hoverNextLevel){
			_hoverNextLevel = true;
			_play_next_level.setTexture(_data->assets.GetTexture("FinishStateNextLevelButtonHover"));
		}
		else if(!_data->input.HoverOverButton(_play_next_level, _data->renderWindow) && _data->renderWindow.hasFocus() &&_hoverNextLevel){
			_hoverNextLevel = false;
			_play_next_level.setTexture(_data->assets.GetTexture("FinishStateNextLevelButton"));
		}

        //Change texture if hovered over menu button
		if(_data->input.HoverOverButton(_menu, _data->renderWindow) && _data->renderWindow.hasFocus() &&!_hoverMainMenu){
			_hoverMainMenu = true;
			_menu.setTexture(_data->assets.GetTexture("FinishStateMainMenuButtonHover"));
		}
		else if(!_data->input.HoverOverButton(_menu, _data->renderWindow) && _data->renderWindow.hasFocus() &&_hoverMainMenu){
			_hoverMainMenu = false;
			_menu.setTexture(_data->assets.GetTexture("FinishStateMainMenuButton"));
		}

		//Check for press play_next button
        if(_data->input.IsSpriteClicked(_play_next_level, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()) {
            if(lastLevel == 1){
                _data->sound._clickSound.play();
                _data->machine.AddState(StateRef(new Level2(_data)), true);
            }
        }

        //Check for press menu button
        if(_data->input.IsSpriteClicked(_menu, sf::Mouse::Left, _data->renderWindow) && _data->renderWindow.hasFocus()){
            _data->sound._clickSound.play();
            _data->machine.AddState( StateRef( new MainMenuState(_data)), true);
            _data->machine.clean_states();
        }

        //Check for press quit button
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