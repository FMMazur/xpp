#include "parser.hxx"

#include <sstream>

namespace xpp {
  Parser::Parser(std::string_view program) : _lexer{new Lexer(program)}, _ltoken{nullptr} {
    currentTable = globalTable = initialize_table();
    _lexer->table(currentTable);
  }

  void Parser::run() {
    advance();

    program();
  }

  void Parser::advance() {
    if (_ltoken && _ltoken->is(Token::Kind::Identifier))
      delete _ltoken;

    _ltoken = _lexer->next();
  }

  void Parser::match(Token::Kind kind) {
    if (_ltoken->is(kind)) {
      advance();
    } else {
      std::stringstream ss;

      ss << "Expected " << format(kind);
      ss << " found " << format_token() << std::endl;
      error(ss.str());
    }
  }

  void Parser::match(Token::OperatorAttribute operatorAttribute) {
    auto kind = Token::Kind::Operator;

    if (_ltoken->is(kind) && _ltoken->op() == operatorAttribute) {
      advance();
    } else {
      std::stringstream ss;

      ss << "Expected " << format(kind, operatorAttribute);
      ss << " found " << format_token() << std::endl;
      error(ss.str());
    }
  }

  void Parser::match(Token::SeparatorAttribute separatorAttribute) {
    auto kind = Token::Kind::Separator;

    if (_ltoken->is(kind) && _ltoken->separator() == separatorAttribute) {
      advance();
    } else {
      std::stringstream ss;

      ss << "Expected " << format(kind, separatorAttribute);
      ss << " found " << format_token() << std::endl;
      error(ss.str());
    }
  }

  std::string Parser::format(Token::Kind kind, std::string_view lexeme) {
    std::stringstream ss;
    ss << kind;

    if (!lexeme.empty()) {
      ss << " -> " << lexeme;
    }

    return ss.str();
  }

  std::string Parser::format(Token::Kind kind, Token::OperatorAttribute operatorAttribute) {
    std::stringstream ss;
    ss << kind;
    ss << " -> " << operatorAttribute;

    return ss.str();
  }

  std::string Parser::format(Token::Kind kind, Token::SeparatorAttribute separatorAttribute) {
    std::stringstream ss;
    ss << kind;
    ss << " -> " << separatorAttribute;

    return ss.str();
  }

  std::string Parser::format_token() {
    std::stringstream ss;

    ss << _ltoken->kind();

    if (_ltoken->has_lexeme()) {
      ss << " -> " << _ltoken->lexeme();
    } else if (_ltoken->is(xpp::Token::Kind::Operator)) {
      ss << " -> " << _ltoken->op();
    } else if (_ltoken->is(xpp::Token::Kind::Separator)) {
      ss << " -> " << _ltoken->separator();
    }

    return ss.str();
  }

  void Parser::error(std::string_view message) {
    std::cout << "Linha " << _lexer->line() << ": " << message << std::endl;
    exit(EXIT_FAILURE);
  }

  SymbolTable *Parser::initialize_table() {
    auto table = new SymbolTable();
    table->add(new Token(Token::Kind::Class, "class"), true);
    table->add(new Token(Token::Kind::Extends, "extends"), true);
    table->add(new Token(Token::Kind::Constructor, "constructor"), true);
    table->add(new Token(Token::Kind::Break, "break"), true);
    table->add(new Token(Token::Kind::Print, "print"), true);
    table->add(new Token(Token::Kind::Read, "read"), true);
    table->add(new Token(Token::Kind::Return, "return"), true);
    table->add(new Token(Token::Kind::Super, "super"), true);
    table->add(new Token(Token::Kind::If, "if"), true);
    table->add(new Token(Token::Kind::Else, "else"), true);
    table->add(new Token(Token::Kind::For, "for"), true);
    table->add(new Token(Token::Kind::New, "new"), true);
    table->add(new Token(Token::Kind::Integer, "int"), true);
    table->add(new Token(Token::Kind::String, "string"), true);

    return table;
  }

  Parser::~Parser() {
    delete _lexer;

    auto table = currentTable;

    while (table) {
      auto parent = table->parent();
      delete table;

      table = parent;
    }
  }

  bool Parser::type() {
    return _ltoken->is_one_of(Token::Kind::Identifier, Token::Kind::String, Token::Kind::Integer);
  }

  bool Parser::possible_statements() {
    return _ltoken->is_one_of(Token::Kind::Identifier, Token::Kind::Print,
                              Token::Kind::Read, Token::Kind::Return, Token::Kind::Super,
                              Token::Kind::If, Token::Kind::For, Token::Kind::Break) ||
           _ltoken->separator() == Token::SeparatorAttribute::Semicolon;
  }

  bool Parser::is_expression() {
    return _ltoken->is_one_of(Token::Kind::StringLiteral, Token::Kind::IntegerLiteral, Token::Kind::Identifier) ||
           _ltoken->separator() == Token::SeparatorAttribute::LeftParen;
  }

  void Parser::program() {
    if (_ltoken->is(Token::Kind::Class)) {
      classList();
    }
  }

  void Parser::classList() {
    do {
      classDecl();
    } while (_ltoken->is(Token::Kind::Class));
  }

  void Parser::classDecl() {
    match(Token::Kind::Class);
    match(Token::Kind::Identifier);

    if (_ltoken->is(Token::Kind::Extends)) {
      advance();

      match(Token::Kind::Identifier);
    }

    classBody();
  }

  void Parser::classBody() {
    match(Token::SeparatorAttribute::LeftBrace);

    classContent();

    //varDeclListOpt();
    //constructDeclListOpt();
    //methodDeclListOpt();

    match(Token::SeparatorAttribute::RightBrace);
  }

  void Parser::classContent() {
    if (_ltoken->is(Token::Kind::Constructor)) {
      constructDeclListOpt();
      methodDeclListOpt();
    }

    if (_ltoken->is(Token::Kind::Identifier)) {
      match(Token::Kind::Identifier);

      if (_ltoken->separator() == Token::SeparatorAttribute::LeftBracket) {
        advance();

        match(Token::SeparatorAttribute::RightBracket);
      }

      if (_ltoken->is(Token::Kind::Identifier)) {
        match(Token::Kind::Identifier);

        declListOpt();
      }
    }
  }

  void Parser::varDeclListOpt() {
    if (type()) {
      varDeclList();
    }
  }

  void Parser::varDeclList() {
    do {
      varDecl();
    } while (type());
  }

  void Parser::varDecl() {
    match(Token::Kind::Identifier);

    if (_ltoken->separator() == Token::SeparatorAttribute::LeftBracket) {
      advance();

      match(Token::SeparatorAttribute::RightBracket);
    }

    varDeclNoAmbiguity();
  }

  void Parser::varDeclNoAmbiguity() {
    match(Token::Kind::Identifier);

    varDeclOpt();

    match(Token::SeparatorAttribute::Semicolon);
  }

  void Parser::varDeclOpt() {
    while (_ltoken->separator() == Token::SeparatorAttribute::Comma) {
      advance();

      match(Token::Kind::Identifier);
    }
  }

  void Parser::declListOpt() {
    if (_ltoken->separator() == Token::SeparatorAttribute::Comma || _ltoken->separator() == Token::SeparatorAttribute::Semicolon) {
      varDeclOpt();

      match(Token::SeparatorAttribute::Semicolon);

      classContent();
    }

    if (_ltoken->separator() == Token::SeparatorAttribute::LeftParen) {
      methodBody();

      methodDeclListOpt();
    }
  }

  void Parser::constructDeclListOpt() {
    if (_ltoken->is(Token::Kind::Constructor)) {
      constructDeclList();
    }
  }

  void Parser::constructDeclList() {
    do {
      constructDecl();
    } while (_ltoken->is(Token::Kind::Constructor));
  }

  void Parser::constructDecl() {
    match(Token::Kind::Constructor);

    methodBody();
  }

  void Parser::methodDeclListOpt() {
    if (type()) {
      methodDeclList();
    }
  }

  void Parser::methodDeclList() {
    do {
      methodDecl();
    } while (type());
  }

  void Parser::methodDecl() {
    match(Token::Kind::Identifier);

    if (_ltoken->separator() == Token::SeparatorAttribute::LeftBracket) {
      advance();

      match(Token::SeparatorAttribute::RightBracket);
    }

    match(Token::Kind::Identifier);

    methodBody();
  }

  void Parser::methodBody() {
    match(Token::SeparatorAttribute::LeftParen);
    paramListOpt();
    match(Token::SeparatorAttribute::RightParen);

    match(Token::SeparatorAttribute::LeftBrace);
    statementsOpt();
    match(Token::SeparatorAttribute::RightBrace);
  }

  void Parser::paramListOpt() {
    if (type()) {
      paramList();
    }
  }

  void Parser::paramList() {
    do {
      param();

      if (_ltoken->separator() == Token::SeparatorAttribute::Comma) {
        advance();
      }
    } while (type());
  }

  void Parser::param() {
    match(Token::Kind::Identifier);

    if (_ltoken->separator() == Token::SeparatorAttribute::LeftBracket) {
      advance();

      match(Token::SeparatorAttribute::RightBracket);
    }

    match(Token::Kind::Identifier);
  }

  void Parser::statementsOpt() {
    if (possible_statements()) {
      statements();
    }
  }

  void Parser::statements() {
    do {
      statement();
    } while (possible_statements());
  }

  void Parser::statement() {
    switch (_ltoken->kind()) {
      case Token::Kind::Identifier:
      case Token::Kind::String:
      case Token::Kind::Integer:
        checkStatementIdentifier();
        break;

      case Token::Kind::Print:
        printStat();

        match(Token::SeparatorAttribute::Semicolon);
        break;

      case Token::Kind::Read:
        readStat();

        match(Token::SeparatorAttribute::Semicolon);
        break;

      case Token::Kind::Return:
        returnStat();

        match(Token::SeparatorAttribute::Semicolon);
        break;

      case Token::Kind::Super:
        superStat();

        match(Token::SeparatorAttribute::Semicolon);
        break;

      case Token::Kind::If:
        ifStat();
        break;

      case Token::Kind::For:
        forStat();
        break;

      case Token::Kind::Break:
        match(Token::Kind::Break);
      default:
        match(Token::SeparatorAttribute::Semicolon);
        break;
    }
  }

  void Parser::atribStat() {
    lvalue();

    match(Token::OperatorAttribute::Assign);

    if (!_ltoken->is(Token::Kind::New)) {
      expression();
    } else {
      allocExpression();
    }
  }

  void Parser::atribStatNoAmbiguity() {
    lvalueNoAmbiguity();

    match(Token::OperatorAttribute::Assign);

    if (!_ltoken->is(Token::Kind::New)) {
      expression();
    } else {
      allocExpression();
    }
  }

  void Parser::atribStatOpt() {
    if (_ltoken->is(Token::Kind::Identifier)) {
      atribStat();
    }
  }

  void Parser::printStat() {
    match(Token::Kind::Print);

    expression();
  }

  void Parser::readStat() {
    match(Token::Kind::Read);
    lvalue();
  }

  void Parser::returnStat() {
    match(Token::Kind::Return);

    expression();
  }

  void Parser::superStat() {
    match(Token::Kind::Super);

    match(Token::SeparatorAttribute::LeftParen);
    argListOpt();
    match(Token::SeparatorAttribute::RightParen);
  }

  void Parser::ifStat() {
    match(Token::Kind::If);

    match(Token::SeparatorAttribute::LeftParen);
    expression();
    match(Token::SeparatorAttribute::RightParen);

    match(Token::SeparatorAttribute::LeftBrace);
    statements();
    match(Token::SeparatorAttribute::RightBrace);

    if (_ltoken->is(Token::Kind::Else)) {
      elseStat();
    }
  }

  void Parser::forStat() {
    match(Token::Kind::For);

    match(Token::SeparatorAttribute::LeftParen);
    atribStatOpt();
    match(Token::SeparatorAttribute::Semicolon);
    expressionOpt();
    match(Token::SeparatorAttribute::Semicolon);
    atribStatOpt();
    match(Token::SeparatorAttribute::RightParen);

    match(Token::SeparatorAttribute::LeftBrace);
    statements();
    match(Token::SeparatorAttribute::RightBrace);
  }

  void Parser::elseStat() {
    match(Token::Kind::Else);

    match(Token::SeparatorAttribute::LeftBrace);
    statements();
    match(Token::SeparatorAttribute::RightBrace);
  }

  void Parser::expressionOpt() {
    if (is_expression()) {
      expression();
    }
  }

  void Parser::expression() {
    numExpression();

    switch (_ltoken->op()) {
      case Token::OperatorAttribute::LessThan:
      case Token::OperatorAttribute::LessEqual:
      case Token::OperatorAttribute::GreaterThan:
      case Token::OperatorAttribute::GreaterEqual:
      case Token::OperatorAttribute::Equal:
      case Token::OperatorAttribute::Different:
        advance();

        numExpression();

        break;
      default:
        break;
    }
  }

  void Parser::allocExpression() {
    if (_ltoken->is(Token::Kind::New)) {
      advance();

      match(Token::Kind::Identifier);

      match(Token::SeparatorAttribute::LeftParen);
      argListOpt();
      match(Token::SeparatorAttribute::RightParen);
    } else {
      match(Token::Kind::Identifier);

      match(Token::SeparatorAttribute::LeftBracket);
      expression();
      match(Token::SeparatorAttribute::RightBracket);
    }

  }

  void Parser::numExpression() {
    term();

    auto op = _ltoken->op();

    if (op == Token::OperatorAttribute::Plus || op == Token::OperatorAttribute::Minus) {
      advance();

      term();
    }
  }

  void Parser::lvalue() {
    match(Token::Kind::Identifier);

    if (_ltoken->separator() == Token::SeparatorAttribute::LeftBracket) {
      advance();

      expression();
      match(Token::SeparatorAttribute::RightBracket);
    }

    lvalueComp();
  }

  void Parser::lvalueNoAmbiguity() {
    if (is_expression()) {
      expression();

      match(Token::SeparatorAttribute::RightBracket);
    }

    lvalueComp();
  }

  void Parser::lvalueComp() {
    while (_ltoken->separator() == Token::SeparatorAttribute::Dot) {
      advance();
      match(Token::Kind::Identifier);

      if (_ltoken->separator() == Token::SeparatorAttribute::LeftBracket) {
        advance();

        expression();
        match(Token::SeparatorAttribute::RightBracket);
      }
    }
  }

  void Parser::term() {
    unary();

    auto op = _ltoken->op();

    if (op == Token::OperatorAttribute::Multiplication || op == Token::OperatorAttribute::Division ||
        op == Token::OperatorAttribute::Mod) {
      advance();

      unary();
    }
  }

  void Parser::unary() {
    auto op = _ltoken->op();

    if (op == Token::OperatorAttribute::Plus || op == Token::OperatorAttribute::Minus) {
      advance();
    }

    factor();
  }

  void Parser::factor() {
    if (_ltoken->is_one_of(Token::Kind::IntegerLiteral, Token::Kind::StringLiteral)) {
      advance();
    } else if (_ltoken->is(Token::Kind::Identifier)) {
      lvalue();
    } else if (_ltoken->separator() == Token::SeparatorAttribute::LeftParen) {
      advance();

      expression();

      match(Token::SeparatorAttribute::RightParen);
    } else {
      std::stringstream ss;

      error("Factor expected, but nothing was found");
    }
  }

  void Parser::argListOpt() {
    if (is_expression()) {
      argList();
    }
  }

  void Parser::argList() {
    do {
      expression();

      if (_ltoken->separator() == Token::SeparatorAttribute::Comma) {
        advance();
      }
    } while (is_expression());
  }

  void Parser::checkStatementIdentifier() {
    match(Token::Kind::Identifier);

    if (_ltoken->separator() == Token::SeparatorAttribute::LeftBracket) {
      advance();

      if (_ltoken->separator() == Token::SeparatorAttribute::RightBracket) {
        advance();

        varDeclNoAmbiguity();
      } else {
        atribStatNoAmbiguity();

        match(Token::SeparatorAttribute::Semicolon);
      }
    } else {
      if (_ltoken->is(Token::Kind::Identifier)) {
        varDeclNoAmbiguity();
      } else {
        atribStatNoAmbiguity();

        match(Token::SeparatorAttribute::Semicolon);
      }
    }

  }

}