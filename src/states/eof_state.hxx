#ifndef XPP_EOF_STATE_HXX
#define XPP_EOF_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct EOFState : BaseState {
    explicit EOFState(EOFState::fsm *machine) : BaseState(machine) {}

    std::optional<Token *> react() override {
      return new Token(Token::Kind::EOF);
    }
  };

}
#endif //XPP_EOF_STATE_HXX
