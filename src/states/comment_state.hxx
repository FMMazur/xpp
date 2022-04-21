#ifndef XPP_COMMENT_STATE_HXX
#define XPP_COMMENT_STATE_HXX

#include "base_state.hxx"

namespace xpp::states {

  struct CommentState : BaseState {
    explicit CommentState(CommentState::fsm * machine) : BaseState(machine) {}

    std::optional<Token*> react() override;
  };

  struct EndCommentState : BaseState {
    explicit EndCommentState(EndCommentState::fsm * machine) : BaseState(machine) {}

    std::optional<Token*> react() override;
  };

}

#endif //XPP_COMMENT_STATE_HXX
