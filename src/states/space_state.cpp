#include "space_state.hxx"

#include "states.hxx"

namespace xpp::states {

  std::optional<Token *> SpaceState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->peek();

    if (std::isspace(currentChar)) {
      if (currentChar == '\n') lexer->next_line();
      lexer->consume();
    } else {
      machine()->change_state(make_state<InitialState>());
    }

    return BaseState::react();
  }

}
