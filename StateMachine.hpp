#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace engine{

    typedef std::unique_ptr<State> StateRef;

    class StateMachine{
    public:
        StateMachine(){}
        ~StateMachine(){}

        void AddState(StateRef newState, bool IsReplacing = true);
        void RemoveState();

        void ProcessStateChanges();

        StateRef& GetActiveState();

        int state_size(){
        	return _states.size();
        }

        void clean_states(){
        	if(!_states.empty()){
				StateRef ns = std::move(_states.top());
				_states = std::stack<StateRef>{};
				_states.push(std::move(ns));
        	}
        }

    private:
        std::stack<StateRef> _states;
        StateRef _newState;

        bool _isRemoving;
        bool _isAdding;
        bool _isReplacing;
    };

}