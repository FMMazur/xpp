#include "comment_state.hxx"
#include "states.hxx"

namespace xpp::states {

  std::optional<Token *> CommentState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->peek();

    switch (currentChar) {
      case '\n':
      case '*':
        machine()->change_state(make_state<EndCommentState>());
        break;
      default:
        lexer->consume();
        break;
    }

    return BaseState::react();
  }

  std::optional<Token *> EndCommentState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->get();

    switch (currentChar) {
      case '\n':
        lexer->next_line();
      case '/':
        machine()->change_state(make_state<InitialState>());
        break;
      default:
        break;
    }

    return BaseState::react();
  }
}
