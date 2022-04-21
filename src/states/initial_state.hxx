#ifndef XPP_INITIAL_STATE_HXX
#define XPP_INITIAL_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {
  struct InitialState : BaseState {
    explicit InitialState(fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override;
  };
}

#endif //XPP_INITIAL_STATE_HXX
