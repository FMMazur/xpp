all:
	g++ main.cpp src/token.cpp src/lexer.cpp src/states/base_state.cpp src/states/initial_state.cpp src/states/less_state.cpp src/states/equal_state.cpp src/states/greater_state.cpp src/states/separator_state.cpp src/states/identifier_state.cpp src/states/different_state.cpp src/states/math_state.cpp src/states/slash_state.cpp src/states/comment_state.cpp src/states/digit_state.cpp src/states/space_state.cpp src/states/string_state.cpp src/table/symbol_table.cpp src/parser.cpp src/fsm/fsm.hxx -o xpp\_compiler -I./src -I./src/table -I./src/states -I./src/fsm -std=c++20

.PHONY: clean

clean:
	rm xpp_compiler