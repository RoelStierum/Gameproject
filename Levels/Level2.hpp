#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "../DEFINITIONS.hpp"
#include "../State.hpp"
#include "../Game.hpp"
#include "../Character.hpp"
#include "../Platform.hpp"

namespace engine{

    class Level2: public State{
    public:
        float gravity = 1500; //25.0f;

        sf::Vector2f start = {100,-200};

        Level2(GameDataRef data);

        void Init() override;

        void HandleInput() override;
        void Update(float dt) override;
        void Draw(float dt) override;

        void Pause() override;
        void Resume() override;

        void restart();

    private:
        GameDataRef _data;

        sf::Sprite _background;
        sf::View CameraPosition;
        float cameraX, cameraY = 0;

        Platform platforms = {_data};

        //flag and clock
        sf::Sprite flag;
        sf::Clock clockFinish;
        bool finished = false;

        Character character;

        sf::Sprite pauseButton;

        //tijd van de het level
        sf::Clock levelTime;
        sf::Text levelTimeText;
        float tijd = 0;

        int levelNumber = 2;

        void characterEndgeOfScreen(const Character& character_, const float& dt);

    };

}