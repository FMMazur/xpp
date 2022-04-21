#include "less_state.hxx"

namespace xpp::states {
  std::optional<Token *> LessState::react() {
    auto lexer = _machine->base();
    lexer->consume();

    auto nextChar = lexer->peek();

    auto kind = Token::Kind::Operator;
    auto operatorAttribute = Token::OperatorAttribute::Unknown;

    if (nextChar == '=') {
      lexer->consume();
      operatorAttribute = Token::OperatorAttribute::LessEqual;
    } else {
      operatorAttribute = Token::OperatorAttribute::LessThan;
    }

    return new Token(kind, operatorAttribute);
  }
}