#ifndef XPP_DIFFERENT_STATE_HXX
#define XPP_DIFFERENT_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct DifferentState : BaseState {
    explicit DifferentState(DifferentState::fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override;
  };

}

#endif //XPP_DIFFERENT_STATE_HXX
