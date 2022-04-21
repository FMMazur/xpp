#ifndef XPP_DIGIT_STATE_HXX
#define XPP_DIGIT_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct DigitState : BaseState {
    explicit DigitState(DigitState::fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override;
  };

}

#endif //XPP_DIGIT_STATE_HXX
