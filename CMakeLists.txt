
set(CMAKE_CXX_FLAGS "-std=c++14")

add_executable(compile
  main.cpp
  symbols.cpp 
  tokens.cpp
  lexer.cpp
)
