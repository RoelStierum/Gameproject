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

    struct GameData{
        StateMachine machine;
        sf::RenderWindow renderWindow;
        AssetManager assets;
        InputManager input;
        SoundManager sound;
    };

    typedef std::shared_ptr<GameData> GameDataRef;

    class Game{
    public:
        Game(unsigned int width, unsigned int height, std::string title);

    private:
        const float dt = 1.0f / FPS; //60 fps
        const float dt60 = 1.0f / 60; //60 fps
        sf::Clock _clock;

        GameDataRef _data = std::make_shared<GameData>();

        void run();
    };

}