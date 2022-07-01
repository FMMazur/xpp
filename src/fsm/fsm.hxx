#ifndef XPP_MACHINE_HXX
#define XPP_MACHINE_HXX

#include "state.hxx"

namespace xpp::fsm {
  template<class T, class R>
  class FSM {
  public:
    FSM() : _currentState{nullptr} {}

    using _state = State<T, R>;

    auto react() {
      return _currentState->react();
    }

    [[maybe_unused]] State<T, R> *state() { return _currentState; }
    virtual void change_state(State<T, R> *newState);

    inline auto base() { return reinterpret_cast<T*>(this); };

  protected:
    [[maybe_unused]] virtual void initial_state() = 0;

  private:
    _state* _currentState;
  };

}

#include "fsm.h"

#endif //XPP_MACHINE_HXX
