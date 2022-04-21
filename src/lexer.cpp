#include "lexer.hxx"

#include "states/states.hxx"

namespace xpp {

  Lexer::Lexer(std::string_view program) : _program{program}, _line{1}, _pos{0} {
  }

  Token* Lexer::next() {
    initial_state();

    while (true) {
      auto token = react();

      if (token.has_value())
        return token.value();
    }
  }

  char Lexer::peek(std::size_t idx) const {
    assert(idx < _program.size() && "should be less than program size");
    return _program[idx];
  }

  void Lexer::initial_state() {
    change_state(new states::InitialState(this));
  }

  Lexer::~Lexer() {
    delete state();
    _pos = 0;
    _line = 0;
    _program = "";
  }
}