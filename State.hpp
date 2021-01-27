#pragma once

namespace engine{

    class State{
    public:
        ///@brief Virtual void initialisation function
        virtual void Init()=0;
        ///@brief Virtual void HandleInput function
        virtual void HandleInput()=0;
        ///@brief Virtual void Update function
        virtual void Update(float dt)=0;
        ///@brief Virtual void Draw function
        virtual void Draw(float dt)=0;
        ///@brief Virtual void Pause function
        virtual void Pause(){}
        ///@brief Virtual void Resume function
        virtual void Resume(){}
    };

}