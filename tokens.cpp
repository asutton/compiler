
#include "tokens.hpp"

#include <cassert>
#include <iostream>


keyword_table::keyword_table()
{
  insert({"true", true_kw});
  insert({"false", false_kw});
  insert({"var", var_kw});
}


const char*
token::name() const
{
  switch (kind) {
  default: break;
  case eof_tok: return "eof";

  // Punctuators and operators
  case lparen_tok: return "lparen";
  case rparen_tok: return "rparen";
  case semicolon_tok: return "semicolon";
  case colon_tok: return "colon";
  case question_tok: return "question";
  case plus_tok: return "plus";
  case minus_tok: return "minus";
  case times_tok: return "times";
  case div_tok: return "div";
  case rem_tok: return "rem";
  case eq_tok: return "eq";

  // Keywords
  case true_kw: return "true";
  case false_kw: return "false";
  case var_kw: return "var";

  // Classes
  case int_tok: return "int";
  case id_tok: return "id";
  }
  assert(false && "invalid token kind");
}


std::ostream& 
operator<<(std::ostream& os, const token& tok)
{
  os << '<' << tok.name();
  if (const int_token* num = dynamic_cast<const int_token*>(&tok))
    os << ',' << num->value;
  else if (const id_token* id = dynamic_cast<const id_token*>(&tok))
    os << ',' << id->str();
  os << '>';
  return os;
}

std::ostream& operator<<(std::ostream& os, const token* ptr)
{
  if (!ptr)
    return os << "<null>";
  else
    return os << *ptr;
}
