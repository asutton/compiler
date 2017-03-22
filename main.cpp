
#include "lexer.hpp"

#include <iterator>
#include <iostream>


int main()
{
  keyword_table keywords;
  symbol_table symbols;

  // Read the input into a string.
  std::string input(std::istreambuf_iterator<char>(std::cin),
                    std::istreambuf_iterator<char>());

  lexer l(keywords, symbols, input);
  while (token* tok = l.lex()) {
    std::cout << tok << '\n';
  }

  return 0;
}
