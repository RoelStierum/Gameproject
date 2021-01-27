
#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace engine{

    class ControlState: public State{
    public:
        ControlState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;


        sf::Sprite _background;
        sf::Sprite _instructions;
        sf::Sprite _back;

        bool _hoverBack = false;
        bool mouseCheck = true;

    };

}

