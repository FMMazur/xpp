#ifndef XPP_IDENTIFIER_STATE_HXX
#define XPP_IDENTIFIER_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct IdentifierState : BaseState {
    explicit IdentifierState(IdentifierState::fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override;

    std::string lexeme;
  };

}

#endif //XPP_IDENTIFIER_STATE_HXX
