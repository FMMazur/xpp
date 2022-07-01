#include "initial_state.hxx"

#include "states.hxx"

namespace xpp::states {

  std::optional<Token *> InitialState::react() {
    auto lexer = _machine->base();
    auto currentChar = lexer->peek();

    if (currentChar == '\0') {
      machine()->change_state(make_state<EOFState>());
    }

    if (currentChar == '<') {
      machine()->change_state(make_state<LessState>());
    }

    if (currentChar == '>') {
      machine()->change_state(make_state<GreaterState>());
    }

    if (currentChar == '=') {
      machine()->change_state(make_state<EqualState>());
    }

    if (currentChar == '!') {
      machine()->change_state(make_state<DifferentState>());
    }

    if (currentChar == '/') {
      machine()->change_state(make_state<SlashState>());
    }

    if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '%') {
      machine()->change_state(make_state<MathState>());
    }

    if (currentChar == '(' || currentChar == ')' || currentChar == '[' || currentChar == ']' ||
        currentChar == '{' || currentChar == '}' || currentChar == '.' || currentChar == ',' ||
        currentChar == ';') {
      machine()->change_state(make_state<SeparatorState>());
    }

    if (std::isalpha(currentChar) || currentChar == '_') {
      machine()->change_state(make_state<IdentifierState>());
    }

    if (currentChar == '"') {
      lexer->consume();
      machine()->change_state(make_state<StringState>());
    }

    if (std::isdigit(currentChar)) {
      lexer->consume();
      machine()->change_state(make_state<DigitState>());
    }

    if (std::isspace(currentChar)) {
      if (currentChar == '\n') lexer->next_line();

      lexer->consume();
      machine()->change_state(make_state<SpaceState>());
    }

    return BaseState::react();
  }

}