#include "Game.hpp"
#include "SplashState.hpp"
#include <SFML/Window.hpp>

namespace engine{

    Game::Game(unsigned int width, unsigned int height, std::string title){
        _data->renderWindow.create(sf::VideoMode{width,height}, title, sf::Style::Close | sf::Style::Titlebar);
        _data->machine.AddState(StateRef(new SplashState(_data)));

        _data->renderWindow.setFramerateLimit(FPS);
        _data->renderWindow.setVerticalSyncEnabled(true);

        //place in middle of screen
        try {
			_data->renderWindow.setPosition(sf::Vector2i{sf::Vector2u{
					sf::VideoMode::getDesktopMode().width / 2 - SCREEN_WIDTH / 2,
					sf::VideoMode::getDesktopMode().height / 2 - SCREEN_HEIGHT / 2}});
		}catch (const std::exception& e){
        	// nothing
        }
        run();
    }

    void Game::run() {
        float newTime, frameTime, interpolation;

        float currentTime = _clock.getElapsedTime().asSeconds();
        float accumulator = 0.0f;

        while(_data->renderWindow.isOpen()){
            _data->machine.ProcessStateChanges();

            newTime = _clock.getElapsedTime().asSeconds();
            frameTime = newTime - currentTime;

            if(frameTime > 0.25f){
                frameTime = 0.25f;
            }

            currentTime = newTime;
            accumulator += frameTime;

            while(accumulator >= dt){
                _data->machine.GetActiveState()->HandleInput();
                _data->machine.GetActiveState()->Update(dt);

                accumulator -= dt;
            }

            interpolation = accumulator / dt;
            _data->machine.GetActiveState()->Draw(interpolation);
        }
    }

}