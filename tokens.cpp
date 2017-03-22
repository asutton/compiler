
#include "tokens.hpp"

#include <cassert>
#include <iostream>
#include <sstream>


keyword_table::keyword_table()
{
  insert({"bool", bool_kw});
  insert({"false", false_kw});
  insert({"int", int_kw});
  insert({"true", true_kw});
  insert({"var", var_kw});
}

const char*
token::name(token_kind kind)
{
  switch (kind) {
  default: break;
  case eof_tok: return "eof_tok";

  // Punctuators and operators
  case lparen_tok: return "lparen_tok";
  case rparen_tok: return "rparen_tok";
  case semicolon_tok: return "semicolon_tok";
  case colon_tok: return "colon_tok";
  case question_tok: return "question_tok";
  case plus_tok: return "plus_tok";
  case minus_tok: return "minus_tok";
  case times_tok: return "times_tok";
  case div_tok: return "div_tok";
  case rem_tok: return "rem_tok";
  case eq_tok: return "eq_tok";

  // Keywords
  case bool_kw: return "bool_kw";
  case false_kw: return "false_kw";
  case int_kw: return "int_kw";
  case true_kw: return "true_kw";
  case var_kw: return "var_kw";

  // Classes
  case int_tok: return "int_tok";
  case id_tok: return "id_tok";
  }
  assert(false && "invalid token kind");
}

const char*
token::str(token_kind kind)
{
  switch (kind) {
  default: break;
  case eof_tok: return "<eof>";

  // Punctuators and operators
  case lparen_tok: return "(";
  case rparen_tok: return ")";
  case semicolon_tok: return ";";
  case colon_tok: return ":";
  case question_tok: return "?";
  case plus_tok: return "+";
  case minus_tok: return "-";
  case times_tok: return "*";
  case div_tok: return "/";
  case rem_tok: return "%";
  case eq_tok: return "=";

  // Keywords
  case bool_kw: return "bool";
  case false_kw: return "false";
  case int_kw: return "int";
  case true_kw: return "true";
  case var_kw: return "var";

  // Classes
  case int_tok: return "integer";
  case id_tok: return "identifier";
  }
  assert(false && "invalid token kind");
}


std::string
int_token::str() const
{
  std::stringstream ss;
  ss << value;
  return ss.str();
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
