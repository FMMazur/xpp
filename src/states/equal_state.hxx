#ifndef XPP_EQUAL_STATE_HXX
#define XPP_EQUAL_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct EqualState : BaseState {
    explicit EqualState(EqualState::fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override;
  };

}

#endif //XPP_EQUAL_STATE_HXX
