#include "comment_state.hxx"

namespace xpp::states {

  std::optional<Token *> CommentState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->peek();

    if (currentChar == '\n' || currentChar == '*') {
      machine()->change_state(make_state<EndCommentState>());
    } else {
      lexer->consume();
    }

    return BaseState::react();
  }

  std::optional<Token *> EndCommentState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->get();

    if (currentChar == '\n' || currentChar == '/') {
      return new Token(Token::Kind::Comment);
    } else if (currentChar == '*') {
     lexer->consume();
    }
    else {
      machine()->change_state(make_state<CommentState>());
    }

    return BaseState::react();
  }
}
