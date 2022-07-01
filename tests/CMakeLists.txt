cmake_minimum_required(VERSION 3.21)

add_executable(lexer lexer.cpp)
add_executable(parser parser.cpp)

target_link_libraries(lexer PRIVATE ${LIBRARY_NAME})
target_link_libraries(parser PRIVATE ${LIBRARY_NAME})
