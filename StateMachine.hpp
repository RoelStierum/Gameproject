#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace engine{

    //Type define of the StateRef type.
    typedef std::unique_ptr<State> StateRef;

    class StateMachine{
    public:
        ///@brief AddState function of the StateMachineClass.
        ///@details This function adds a state to the StateMachine.
        void AddState(StateRef newState, bool IsReplacing = true);

        ///@brief RemoveState function of the StateMachineClass.
        ///@details This function removes the top state on ProcessStateChanges.
        void RemoveState();

        ///@brief ProcessStateChanges function of the StateMachineClass.
        ///@details This function updates the StateMachine.
        void ProcessStateChanges();

        ///@brief GetActiveState function of the StateMachineClass.
        ///@details This function returns the top state.
        StateRef& GetActiveState();

        ///@brief clean_states function of the StateMachineClass.
        ///@details This function cleans the stateMachine to only the top state.
        void clean_states();

    private:
        std::stack<StateRef> _states;
        StateRef _newState;

        bool _isRemoving;
        bool _isAdding;
        bool _isReplacing;
    };

}