#include "slash_state.hxx"

#include "states.hxx"

namespace xpp::states {

  std::optional<Token *> SlashState::react() {
    auto lexer = _machine->base();
    lexer->consume();

    auto currentChar = lexer->peek();

    if (currentChar == '/' || currentChar == '*') {
      lexer->consume();
      machine()->change_state(make_state<CommentState>());
    } else {
      lexer->undo();
      machine()->change_state(make_state<MathState>());
    }

    return BaseState::react();
  }

}
