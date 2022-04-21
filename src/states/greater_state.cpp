#include "greater_state.hxx"

namespace xpp::states {

  std::optional<Token *> GreaterState::react() {
    auto lexer = _machine->base();
    lexer->consume();

    auto currentChar = lexer->peek();

    auto kind = Token::Kind::Operator;
    auto operatorAttribute = Token::OperatorAttribute::Unknown;

    if (currentChar == '=') {
      lexer->consume();
      operatorAttribute = Token::OperatorAttribute::GreaterEqual;
    } else {
      operatorAttribute = Token::OperatorAttribute::GreaterThan;
    }

    return new Token(kind, operatorAttribute);
  }

}
