#ifndef XPP_TOKEN_HXX
#define XPP_TOKEN_HXX

#include <string_view>
#include <variant>
#include <optional>
#include <iostream>

#undef EOF

namespace xpp {

  class Token {
  public:
    enum class Kind : short;
    enum class OperatorAttribute : short;
    enum class SeparatorAttribute : short;

  public:
    using Attribute = std::variant<OperatorAttribute, SeparatorAttribute>;

    Token() = delete;

    explicit Token(Kind kind);

    Token(Kind type, std::optional<std::variant<std::string_view, Attribute>> attr);

    Kind kind() noexcept;

    bool is(Kind kind) noexcept;

    bool is_not(Kind kind) noexcept;

    [[nodiscard]] bool is_not(Kind kind) const noexcept;

    //bool is_one_of(Kind)
    [[nodiscard]] bool is(Kind kind) const noexcept {
      return kind == _kind;
    }

    [[nodiscard]] bool is_one_of(Kind k1, Kind k2) const noexcept { return is(k1) || is(k2); }

    template<class... Ts>
    bool is_one_of(Kind kind1, Kind kind2, Ts... kinds) const noexcept {
      return is(kind1) || is_one_of(kind2, kinds...);
    }

    [[nodiscard]] bool has_lexeme() const noexcept;

    [[nodiscard]] std::string_view lexeme() const noexcept;

    void lexeme(std::string_view lexeme) noexcept;


    [[nodiscard]] bool is_op();

    [[nodiscard]] OperatorAttribute op();

    void op(OperatorAttribute operatorAttribute);

    [[nodiscard]] bool is_separator();

    [[nodiscard]] SeparatorAttribute separator();

    void separator(SeparatorAttribute separatorAttribute);

  private:
    Kind _kind;
    std::optional<std::variant<std::string_view, Attribute>> _attr;

  public:
    enum class Kind : short {
      Identifier, Operator, Separator,

      StringLiteral, IntegerLiteral,

      Integer, String, Class, Extends, Constructor, Break, Print, Read, Return, Super, If, Else, For, New,

      Comment, Undef, EOF
    };

    enum class OperatorAttribute : short {
      Assign, // =
      LessThan,  // <
      LessEqual, // <=
      GreaterThan, // >
      GreaterEqual, // >=
      Equal, // ==
      Different, // !=
      Plus, // +
      Minus, // -
      Multiplication, // *
      Division, // /
      Mod, // %

      Unknown
    };
    enum class SeparatorAttribute : short {
      LeftParen, // (
      RightParen, // )
      LeftBracket, // [
      RightBracket, // ]
      LeftBrace, // {
      RightBrace, // }

      Semicolon, // ;
      Dot, // .
      Comma, // ,

      Unknown
    };
  };

}


inline std::ostream &operator<<(std::ostream &os, const xpp::Token::Kind &kind) {
  static const char *const names[]{"Identifier", "Operator", "Separator",
                                   "StringLiteral", "IntegerLiteral",
                                   "Integer", "String", "Class", "Extends", "Constructor", "Break", "Print", "Read",
                                   "Return", "Super", "If", "Else", "For", "New", "Comment", "Undef", "EOF",};

  return os << names[static_cast<int>(kind)];
}


inline std::ostream &operator<<(std::ostream &os, const xpp::Token::OperatorAttribute &operatorAttribute) {
  static const char *const names[]{"Assign", // =
                                   "LessThan",  // <
                                   "LessEqual", // <=
                                   "GreaterThan", // >
                                   "GreaterEqual", // >=
                                   "Equal", // ==
                                   "Different", // !=
                                   "Plus", // +
                                   "Minus", // -
                                   "Multiplication", // *
                                   "Division", // /
                                   "Mod", // %

                                   "Unknown"};
  return os << names[static_cast<int>(operatorAttribute)];
}

inline std::ostream &operator<<(std::ostream &os, const xpp::Token::SeparatorAttribute &separatorAttribute) {
  static const char *const names[]{"LeftParen", // (
                                   "RightParen", // )
                                   "LeftBracket", // [
                                   "RightBracket", // ]
                                   "LeftBrace", // {
                                   "RightBrace", // }

                                   "Semicolon", // ;
                                   "Dot", // .
                                   "Comma", // ,

                                   "Unknown"};
  return os << names[static_cast<int>(separatorAttribute)];
}

#endif //XPP_TOKEN_HXX
