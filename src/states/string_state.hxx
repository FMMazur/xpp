#ifndef XPP_STRING_STATE_HXX
#define XPP_STRING_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct StringState : BaseState {
    explicit StringState(StringState::fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override;
  };

}

#endif //XPP_STRING_STATE_HXX
