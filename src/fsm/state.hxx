#ifndef XPP_STATE_HXX
#define XPP_STATE_HXX

#include <optional>

namespace xpp::fsm {
  template<class T, class R>
  class FSM;

  template<class T, class R>
  struct State {
    using state = State<T, R>;
    using fsm = FSM<T, R>;

    State() = delete;

    virtual ~State() { _machine = nullptr; }

    explicit State(fsm *machine) : _machine{machine} {
    }

    virtual void enter() = 0;

    virtual R react() = 0;

    virtual void exit() = 0;

    template<class StateToCheck>
    bool is() { return typeid(StateToCheck) == typeid(this); }

    inline fsm *machine() const { return _machine; }

    template<class S>
    inline State<T, R>* make_state() {
      return new S(_machine);
    }
  protected:
    fsm *_machine;
  };
}
#endif //XPP_STATE_HXX
