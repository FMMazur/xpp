#include "different_state.hxx"

namespace xpp::states {

  std::optional<Token *> DifferentState::react() {
    auto lexer = _machine->base();
    lexer->consume();

    auto currentChar = lexer->peek();

    auto kind = Token::Kind::Operator;
    auto operatorAttribute = Token::OperatorAttribute::Unknown;

    if (currentChar == '=') {
      lexer->consume();
      operatorAttribute = Token::OperatorAttribute::Different;
    }

    return new Token(kind, operatorAttribute);
  }

}
