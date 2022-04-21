#include "digit_state.hxx"

namespace xpp::states {

  std::optional<Token *> DigitState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->peek();

    if (std::isdigit(currentChar)) {
      lexer->consume();
    } else {
      return new Token(Token::Kind::Integer);
    }

    return BaseState::react();
  }

}
