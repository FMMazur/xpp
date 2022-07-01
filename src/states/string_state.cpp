#include "string_state.hxx"

namespace xpp::states {

  std::optional<Token *> StringState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->get();

    if (currentChar == '"') {
      return new Token(Token::Kind::StringLiteral);
    }

    return BaseState::react();
  }

}
