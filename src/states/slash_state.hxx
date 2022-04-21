#ifndef XPP_SLASH_STATE_HXX
#define XPP_SLASH_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct SlashState : BaseState {
    explicit SlashState(SlashState::fsm * machine) : BaseState(machine) {}

    std::optional<Token*> react() override;
  };

}

#endif //XPP_SLASH_STATE_HXX
