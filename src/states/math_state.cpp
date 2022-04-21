#include "math_state.hxx"

namespace xpp::states {

  std::optional<Token *> MathState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->get();

    auto kind = Token::Kind::Operator;
    auto operatorAttribute = Token::OperatorAttribute::Unknown;

    if (currentChar == '+') {
      operatorAttribute = Token::OperatorAttribute::Plus;
    }

    if (currentChar == '-'){
      operatorAttribute = Token::OperatorAttribute::Minus;
    }

    if (currentChar == '*'){
      operatorAttribute = Token::OperatorAttribute::Multiplication;
    }

    if (currentChar == '/'){
      operatorAttribute = Token::OperatorAttribute::Division;
    }

    if (currentChar == '%'){
      operatorAttribute = Token::OperatorAttribute::Mod;
    }

    return new Token(kind, operatorAttribute);
  }

}
