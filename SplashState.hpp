#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace engine{

    class SplashState: public State{
    public:
        ///@brief SplashState class constructor.
        ///@details This constructor sets the _data member.
        ///@param data GameDataRef for the _data member.
        SplashState(GameDataRef data);

        ///@brief Init function of the SplashState class.
        ///@details Function that runs on the initialization of the class.
        void Init();

        ///@brief HandleInput function of the SplashState class.
        ///@details Function that handles all the inputs.
        void HandleInput();

        ///@brief Update function of the SplashState class.
        ///@details Function that handles all the updates.
        void Update(float dt);

        ///@brief Draw function of the SplashState class.
        ///@details Function that handles the drawing on the render window.
        void Draw(float dt);

    private:
        GameDataRef _data;

        sf::Clock _clock;

        sf::Texture _backgroundTexture;
        sf::Sprite _background;
    };

}
