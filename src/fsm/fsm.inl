#include "fsm.hxx"

#include "state.hxx"

namespace xpp::fsm {
  template<class T, class R>
  void FSM<T, R>::change_state(State<T, R>* newState) {
    if (_currentState) {
      _currentState->exit();
      delete _currentState;
    }

    _currentState = newState;

    if (_currentState) {
      _currentState->enter();
    }
  }
}