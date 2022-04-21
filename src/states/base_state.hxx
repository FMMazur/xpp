#ifndef XPP_BASE_STATE_HXX
#define XPP_BASE_STATE_HXX

#include <optional>

#include "token.hxx"
#include "fsm/state.hxx"
#include "fsm/fsm.hxx"
#include "lexer.hxx"

namespace xpp {
  class Lexer;

  namespace states {
    using LexerState = fsm::State<Lexer, std::optional<Token *>>;

    struct BaseState : LexerState {
      explicit BaseState(fsm *machine);

      void enter() override {}

      std::optional<Token *> react() override;

      void exit() override {}
    };

  }
}

#endif //XPP_BASE_STATE_HXX
