cmake_minimum_required(VERSION 3.16.3)

project(kmir)

add_executable(${PROJECT_NAME}
src/interpreter.cpp
src/lexer.cpp 
src/main.cpp 
src/nodes.cpp 
src/number.cpp 
src/parser.cpp
src/position.cpp 
src/token.cpp 
)