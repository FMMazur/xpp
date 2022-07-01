#include <iostream>
#include <memory>

#include "lexer.hxx"
#include "token.hxx"

int main() {
  std::string program = "(a ; b ;//simple comment\n /* block comment */\n123 + - * / % = < > <= != >= == () [] {} , . \"string\" asd)";
  xpp::Lexer lexer{program};

  std::unique_ptr<xpp::Token> token;

  do {
    token.reset(lexer.next());

    std::cout << token->kind();

    if (token->has_lexeme()) {
      std::cout << " -> " << token->lexeme() << std::endl;
    }
    else if (token->is(xpp::Token::Kind::Operator)) {
      std::cout << " -> " << token->op() << std::endl;
    }
    else if (token->is(xpp::Token::Kind::Separator)) {
      std::cout << " -> " << token->separator() << std::endl;
    }
    else {
      std::cout << std::endl;
    }
  } while(token->is_not(xpp::Token::Kind::EOF));

  return 0;
}
