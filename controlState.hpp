
#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace engine{
    ///@brief ControlState Class
    ///@details Class to display the instructions to play the game
    class ControlState: public State{
    public:

        ControlState(GameDataRef data);
        ///@brief Initialisation function.
        ///@details Initialisation function for the loading the data assets from the images.
        void Init();
        ///@brief Input function for mouse.
        ///@details Function which interacts with the buttons, for instance the highlighting and clicking.
        void HandleInput();
        ///@brief Update function.
        ///@details Function for using the esc key to exit the instructions screen.
        void Update(float dt);
        ///@brief Draw function.
        ///@details Function for drawing the images on the screen
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

