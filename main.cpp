
#include "lexer.hpp"
#include "parser.hpp"
#include "context.hpp"

#include <iterator>
#include <iostream>


/// Defines the language's keywords.
keyword_table keywords;

/// Stores the language's symbols.
symbol_table symbols;

// Stores language facilities.
context cxt;


void
lex_only(const std::string& input)
{
  // Lex the input and print all of the tokens.
  lexer l(keywords, symbols, input);
  while (token* tok = l.lex())
    std::cout << tok << '\n';
}


int main()
{
  // Read the input into a string.
  std::string input(std::istreambuf_iterator<char>(std::cin),
                    std::istreambuf_iterator<char>());

  // lex_only(input);


  parser p(keywords, symbols, cxt, input);
  p.program();

  return 0;
}
