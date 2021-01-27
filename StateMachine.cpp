#include "StateMachine.hpp"

namespace engine{

    //AddState function for adding a state to the StateMachine.
    void StateMachine::AddState(StateRef newState, bool IsReplacing) {
        _isAdding=true;
        _isReplacing = IsReplacing;

        _newState = std::move(newState);
    }

    //RemoveState function for removing the top state on ProcessStateChanges.
    void StateMachine::RemoveState() {
        _isRemoving = true;
    }

    //ProcessStateChanges function for updating the StateMachine.
    void StateMachine::ProcessStateChanges() {
        if(_isRemoving && !_states.empty()){
            _states.pop();

            if(!_states.empty()){
                _states.top()->Resume();
            }

            _isRemoving = false;
        }

        if(_isAdding){
            if(!_states.empty()){
                if(_isReplacing){
                    _states.pop();
                }
                else{
                    _states.top()->Pause();
                }
            }

            _states.push(std::move(_newState));
            _states.top()->Init();
            _isAdding = false;
        }
    }

    //GetActiveState function for returning the top state.
    StateRef& StateMachine::GetActiveState() {
        return _states.top();
    }

    //clean_states function for cleaning the stateMachine to only the top state.
    void StateMachine::clean_states() {
        if(!_states.empty()){
            StateRef ns = std::move(_states.top());
            _states = std::stack<StateRef>{};
            _states.push(std::move(ns));
        }
    }

}