#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.hpp"
#include "InputManager.hpp"
#include "AssetManager.hpp"
#include "SoundManager.hpp"
#include "DEFINITIONS.hpp"

namespace engine{

    ///@brief GameData struct.
    ///@details Struct containing the basic managers and machines of the game.
    struct GameData{
        StateMachine machine;
        sf::RenderWindow renderWindow;
        AssetManager assets;
        InputManager input;
        SoundManager sound;
    };

    ///@brief GameDataRef type
    ///@details Type define of the GameDataRef type.
    typedef std::shared_ptr<GameData> GameDataRef;

    ///@brief Game class
    ///@details This class starts the game and Initializes the first state
    class Game{
    public:
        ///@brief TemplateLevel class constructor
        ///@details This constructor makes a render window with the width, height and title given.
        ///@param width The width of the render window
        ///@param height The height of the render window
        ///@param title The title of the render window
        Game(unsigned int width, unsigned int height, std::string title);

    private:
        const float dt = 1.0f / FPS; //draw dt is variable
        const float dt60 = 1.0f / 60; //update dt is locked at 60 Hz
        sf::Clock _clock;

        GameDataRef _data = std::make_shared<GameData>();

        void run();
    };

}