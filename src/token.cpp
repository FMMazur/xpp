#include "token.hxx"
#include <cassert>

namespace xpp {
  Token::Token(Kind kind) : _kind{kind} {}

  Token::Token(Token::Kind type,
               std::optional<std::variant<std::string_view, Attribute>> attr)
      : _kind{type},
        _attr{attr} {}

  Token::Kind Token::kind() noexcept {
    return _kind;
  }

  bool Token::is(Token::Kind kind) noexcept {
    return kind == _kind;
  }

  bool Token::is_not(Kind kind) noexcept {
    return kind != _kind;
  }

  bool Token::is_not(Token::Kind kind) const noexcept {
    return kind != _kind;
  }

  std::string_view Token::lexeme() const noexcept {
    if (!has_lexeme()) return std::string_view{};

    return std::get<std::string_view>(_attr.value());
  }

  bool Token::has_lexeme() const noexcept {
    if (!Token::is_one_of(Kind::Identifier, Kind::Class, Kind::Constructor, Kind::Extends, Kind::Break, Kind::Print,
                         Kind::Read, Kind::Return, Kind::Super, Kind::If, Kind::Else, Kind::For, Kind::New))
      return false;

    if (!_attr.has_value()) return false;

    auto variant{_attr.value()};

    return std::holds_alternative<std::string_view>(variant);
  }

  void Token::lexeme(std::string_view lexeme) noexcept {
    _attr = lexeme;
  }

  Token::OperatorAttribute Token::op() {
    if (!is_op()) return OperatorAttribute::Unknown;
    auto attribute = std::get<Attribute>(_attr.value());

    return std::get<OperatorAttribute>(attribute);
  }

  void Token::op(Token::OperatorAttribute operatorAttribute) {
    _kind = Kind::Operator;
    _attr = operatorAttribute;
  }

  bool Token::is_op() {
    if (!_attr.has_value()) return false;

    auto variant{_attr.value()};

    if (!std::holds_alternative<Attribute>(variant)) return false;

    auto attribute = std::get<Attribute>(variant);

    return std::holds_alternative<OperatorAttribute>(attribute);
  }

  bool Token::is_separator() {
    if (!_attr.has_value()) return false;

    auto variant{_attr.value()};

    if (!std::holds_alternative<Attribute>(variant)) return false;

    auto attribute = std::get<Attribute>(variant);

    return std::holds_alternative<SeparatorAttribute>(attribute);
  }

  Token::SeparatorAttribute Token::separator() {
    if (!is_separator()) return SeparatorAttribute::Unknown;
    auto attribute = std::get<Attribute>(_attr.value());

    return std::get<SeparatorAttribute>(attribute);
  }

  void Token::separator(Token::SeparatorAttribute separatorAttribute) {
    _kind = Kind::Separator;
    _attr = separatorAttribute;
  }
}
