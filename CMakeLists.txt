cmake_minimum_required(VERSION 3.21)
project(
        xpp
        LANGUAGES CXX
        VERSION 0.1.0
)

option(BUILD_TESTS "Enable tests build" ON)

# TODO: separate library from main executable

set(CMAKE_CXX_STANDARD 20)

set(LIBRARY_NAME xpp_lib)
set(LIBRARY_SRC
        src/token.cpp
        src/lexer.cpp
        src/fsm/fsm.inl
        src/states/base_state.cpp
        src/states/initial_state.cpp
        src/states/less_state.cpp
        src/states/equal_state.cpp
        src/states/greater_state.cpp
        src/states/separator_state.cpp
        src/states/identifier_state.cpp
        src/states/different_state.cpp
        src/states/math_state.cpp
        src/states/slash_state.cpp
        src/states/comment_state.cpp
        src/states/digit_state.cpp src/states/digit_state.hxx src/states/space_state.cpp src/states/space_state.hxx src/states/string_state.cpp src/states/string_state.hxx)

add_library(${LIBRARY_NAME} OBJECT ${LIBRARY_SRC})
set_target_properties(${LIBRARY_NAME} PROPERTIES CMAKE_CXX_STANDARD 20)
target_include_directories(${LIBRARY_NAME} PUBLIC src/)

if (BUILD_TESTS)
add_subdirectory(tests)
endif()