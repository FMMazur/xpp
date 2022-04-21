#ifndef XPP_SEPARATOR_STATE_HXX
#define XPP_SEPARATOR_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct SeparatorState : BaseState {
    explicit SeparatorState(SeparatorState::fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override;
  };

}

#endif //XPP_SEPARATOR_STATE_HXX
