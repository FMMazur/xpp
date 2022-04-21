#ifndef XPP_LESS_STATE_HXX
#define XPP_LESS_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct LessState : BaseState {
    explicit LessState(LessState::fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override;
  };

}

#endif //XPP_LESS_STATE_HXX
