#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace engine{

    typedef std::unique_ptr<State> StateRef;

    class StateMachine{
    public:
        void AddState(StateRef newState, bool IsReplacing = true);
        void RemoveState();

        void ProcessStateChanges();

        StateRef& GetActiveState();

        int state_size();

        void clean_states();

    private:
        std::stack<StateRef> _states;
        StateRef _newState;

        bool _isRemoving;
        bool _isAdding;
        bool _isReplacing;
    };

}