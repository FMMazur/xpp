cmake_minimum_required(VERSION 3.21)

add_executable(lexer lexer.cpp)
target_link_libraries(lexer PRIVATE ${LIBRARY_NAME})
