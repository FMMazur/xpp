#ifndef XPP_LEXER_HXX
#define XPP_LEXER_HXX

#include <vector>
#include <string_view>
#include <cassert>
#include "token.hxx"
#include "fsm/fsm.hxx"
#include "table/symbol_table.hxx"

namespace xpp {

  class Lexer : fsm::FSM<Lexer, std::optional<Token *>> {
  public:
    Lexer() = delete;

    explicit Lexer(std::string_view program);

    virtual ~Lexer();

    Token *next();

    [[nodiscard]] inline std::size_t pos() const {
      return _pos;
    }

    [[nodiscard]] inline char peek() const noexcept {
      assert(_pos <= _program.length() && "should be less than program size");

      return _program[_pos];
    }

    [[nodiscard]] inline char peek(std::size_t idx) const;

    [[nodiscard]] inline char last() const {
      assert(_pos > 0 && "should be more than position 0");

      return _program[_pos - 1];
    }

    [[maybe_unused]] inline char get() noexcept {
      return _program[_pos++];
    }

    inline void consume() { _pos++; }

    inline void undo() { _pos--; }

    inline void next_line() { _line++; }
    inline std::size_t line() { return _line; }

    inline SymbolTable *table() { return _symbolTable; };
    inline void table(SymbolTable * symbolTable) { _symbolTable = symbolTable; };

    friend struct fsm::State<Lexer, std::optional<Token *>>;

  protected:
    void initial_state() override;

  private:
    std::string_view _program;
    std::size_t _pos;
    std::size_t _line;

    SymbolTable *_symbolTable{nullptr};
  };

}

#endif //XPP_LEXER_HXX
