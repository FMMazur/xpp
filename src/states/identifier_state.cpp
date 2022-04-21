#include "identifier_state.hxx"

namespace xpp::states {

  std::optional<Token *> IdentifierState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->peek();

    if (std::isalnum(currentChar)) {
      lexeme.push_back(currentChar);
      lexer->consume();
    } else {
      // TODO: check if in keyword table
      return new Token(Token::Kind::Identifier, lexeme);
    }

    return BaseState::react();
  }

}
