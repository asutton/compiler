#pragma once

#include "tokens.hpp"

#include <vector>


/// The lexer is responsible for transforming input chracters into tokens
/// according to the following rules.
///
/// Punctuators and operators are tokens and are the following characters:
///
///   ( ) ; : ? + - * / % =
///
/// Keywords are tokens and are the following reserved words.
///
///   true false var
///
/// Integer literals are tokens defined by the following pattern:
///
///   integer-literals -> digit digit*
///
///   digit -> [0-9]
///
/// Identifiers are tokens and are defined by the following pattern:
///
///   identifer -> (letter | '_') (letter | digit | '_')*
///
///   letter -> [a-zA-Z]
///
/// The lexer operates over a range of characters, represented by a pair of
/// pointers. Tokens created by the lexer are destroyed along with the
/// lexer.
struct lexer
{
  lexer(const keyword_table&, symbol_table&, const char*, const char*);
  lexer(const keyword_table&, symbol_table&, const std::string&);
  ~lexer();

  token* lex();

private:
  /// Returns true if the lexer is at the end of input.
  bool eof() const;

  /// Returns the current lookahead character.
  char lookahead() const;
  
  /// Consume the current chracter and return it. This advances to the next
  /// input character.
  char consume();

  /// Ignore the curretn character. This advaces to the next input character.
  void ignore();

  /// Consume whitespace.
  void space();

  /// Match a single-character punctuator or operator.
  token* puncop(token_kind);

  /// Match a word (identifier or keyword).
  token* word();

  /// Match an integer literal.
  token* integer();

  /// The keyword table associates reserved words with token names.
  const keyword_table* kws;

  /// A symbol table that stores identifiers.
  symbol_table* syms;

  /// The input characters.
  const char* first;
  const char* limit;

  /// Stores characters that form the current token.
  std::string buf;

  /// Stores each token created by the lexer. These are deleted when the
  /// lexer is destroyed.
  std::vector<token*> toks;
};
