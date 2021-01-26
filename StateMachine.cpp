#include "StateMachine.hpp"

namespace engine{

    void StateMachine::AddState(StateRef newState, bool IsReplacing) {
        _isAdding=true;
        _isReplacing = IsReplacing;

        _newState = std::move(newState);
    }

    void StateMachine::RemoveState() {
        _isRemoving = true;
    }

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

    StateRef& StateMachine::GetActiveState() {
        return _states.top();
    }

    int StateMachine::state_size() {
        return _states.size();
    }

    void StateMachine::clean_states() {
        if(!_states.empty()){
            StateRef ns = std::move(_states.top());
            _states = std::stack<StateRef>{};
            _states.push(std::move(ns));
        }
    }

}