#ifndef XPP_GREATER_STATE_HXX
#define XPP_GREATER_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

struct GreaterState : BaseState {
  explicit GreaterState(GreaterState::fsm * machine) : BaseState(machine) {}

  std::optional<Token*> react() override;
};

}

#endif //XPP_GREATER_STATE_HXX
