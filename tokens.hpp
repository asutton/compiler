#pragma once

#include "symbols.hpp"

#include <iosfwd>
#include <string>
#include <unordered_map>


/// Represents the names of tokens.
enum token_kind {
  eof_tok,

  // Punctuators and operators
  lparen_tok,
  rparen_tok,
  semicolon_tok,
  colon_tok,
  question_tok,
  plus_tok,
  minus_tok,
  times_tok,
  div_tok,
  rem_tok,
  eq_tok,

  // Keywords
  true_kw,
  false_kw,
  var_kw,

  // Classes
  int_tok,
  id_tok,
};


/// The keyword table associates reserved words with their corresponding
/// token names.
struct keyword_table : std::unordered_map<std::string, token_kind>
{
  keyword_table();
};


/// Represents individual symbols in the input source. Derived classes provide
/// additional attributes for a token.
struct token
{
  virtual ~token() = default;

  token(token_kind k) : kind(k) { }

  /// Returns the token name.
  const char* name() const;

  token_kind kind;
};


/// Integer tokens contain their integer value.
struct int_token : token
{
  int_token(int n) : token(int_tok), value(n) { }
  
  /// The integer value.
  int value;
};


/// Identifiers contain their symbol.
///
/// \todo This should be a pointer to the symbol stored in the symbol table.
struct id_token : token
{
  id_token(symbol s) : token(id_tok), sym(s) { }

  /// Returns the string representation of the identifier.
  const std::string& str() const { return *sym; }
  
  /// The symbol spelling the identifier.
  symbol sym;
};


/// Print the token to an output stream.
std::ostream& operator<<(std::ostream&, const token&);
std::ostream& operator<<(std::ostream&, const token*);

