#ifndef XPP_MATH_STATE_HXX
#define XPP_MATH_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct MathState : BaseState {
    explicit MathState(MathState::fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override;

    std::string lexeme;
  };

}

#endif //XPP_MATH_STATE_HXX
