#ifndef XPP_SPACE_STATE_HXX
#define XPP_SPACE_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct SpaceState : BaseState {
    explicit SpaceState(SpaceState::fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override;
  };

}

#endif //XPP_SPACE_STATE_HXX
