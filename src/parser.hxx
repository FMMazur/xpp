#ifndef XPP_PARSER_HXX
#define XPP_PARSER_HXX

#include "lexer.hxx"

#include <string>

namespace xpp {

  class Parser {
  public:
    explicit Parser(std::string_view program);

    virtual ~Parser();

    void run();

// states
  private:
    void program();

    void classList();
    void classDecl();
    void classBody();

    void varDeclListOpt();
    void varDeclList();
    void varDecl();
    void varDeclNoAmbiguity();
    void varDeclOpt();

    void constructDeclListOpt();
    void constructDeclList();
    void constructDecl();

    void methodDeclListOpt();
    void methodDeclList();
    void methodDecl();

    void methodBody();

    void paramListOpt();
    void paramList();
    void param();

    void statementsOpt();
    void statements();
    void statement();

    void atribStat();
    void atribStatOpt();
    void atribStatNoAmbiguity();

    void printStat();
    void readStat();
    void returnStat();
    void superStat();
    void ifStat();
    void elseStat();

    void forStat();

    void expressionOpt();
    void expression();

    void allocExpression();
    void numExpression();

    void lvalue();
    void lvalueNoAmbiguity();
    void lvalueComp();

    void term();

    void unary();

    void factor();

    void argListOpt();
    void argList();

    bool type();
    bool is_expression();
    bool possible_statements();

    void checkStatementIdentifier();

  private:
    void advance();

    void match(Token::Kind kind);
    void match(Token::OperatorAttribute operatorAttribute);
    void match(Token::SeparatorAttribute separatorAttribute);

    void error(std::string_view message);
    static std::string format(Token::Kind kind, std::string_view lexeme = "");
    static std::string format(Token::Kind kind, Token::OperatorAttribute operatorAttribute);
    static std::string format(Token::Kind kind, Token::SeparatorAttribute separatorAttribute);
    std::string format_token();

  private:
    static SymbolTable *initialize_table();

  private:
    Lexer *_lexer;

    Token *_ltoken;

    SymbolTable *globalTable;
    SymbolTable *currentTable;
  };

}

#endif //XPP_PARSER_HXX
