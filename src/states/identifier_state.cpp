#include "identifier_state.hxx"

namespace xpp::states {

  std::optional<Token *> IdentifierState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->peek();

    if (std::isalnum(currentChar)) {
      lexeme.push_back(currentChar);
      lexer->consume();
    } else {
      auto table = lexer->table();

      if (table) {
        auto existIdentifier = table->get(lexeme);

        if (existIdentifier)
          return existIdentifier->token;
      }

      return new Token(Token::Kind::Identifier, lexeme);;
    }

    return BaseState::react();
  }

}
