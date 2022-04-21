#include "base_state.hxx"

namespace xpp::states {

  BaseState::BaseState(BaseState::fsm *machine) : BaseState::state(machine) {}

  std::optional<Token *> BaseState::react() {
    return std::nullopt;
  }

}
