#include "separator_state.hxx"

namespace xpp::states {

  std::optional<Token *> SeparatorState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->get();
    auto separatorAttribute = Token::SeparatorAttribute::Unknown;

    if (currentChar == ';') {
      separatorAttribute = Token::SeparatorAttribute::Semicolon;
    }
    if (currentChar == ',') {
      separatorAttribute = Token::SeparatorAttribute::Comma;
    }
    if (currentChar == '.') {
      separatorAttribute = Token::SeparatorAttribute::Dot;
    }

    if (currentChar == '(') {
      separatorAttribute = Token::SeparatorAttribute::LeftParen;
    }
    if (currentChar == ')') {
      separatorAttribute = Token::SeparatorAttribute::RightParen;
    }
    if (currentChar == '[') {
      separatorAttribute = Token::SeparatorAttribute::LeftBracket;
    }
    if (currentChar == ']') {
      separatorAttribute = Token::SeparatorAttribute::RightBracket;
    }
    if (currentChar == '{') {
      separatorAttribute = Token::SeparatorAttribute::LeftBrace;
    }
    if (currentChar == '}') {
      separatorAttribute = Token::SeparatorAttribute::RightBrace;
    }

    return new Token(Token::Kind::Separator, separatorAttribute);
  }

}
