#include "parser.hpp"

#include <cassert>
#include <iostream>
#include <sstream>


parser::parser(const keyword_table& kt, symbol_table& st, context& cxt, const std::string& str)
  : lex(kt, st, str), sema(cxt)
{
  // Queue the first token.
  if (token* tok = lex.lex())
    toks.push_front(tok);
}

bool
parser::eof()
{
  return toks.empty();
}

token*
parser::peek()
{
  if (!toks.empty())
    return toks.front();
  else
    return nullptr;
}

token*
parser::peek(int n)
{
  // peek(0) is equivalent to peek().
  if (n == 0)
    return peek();

  // We already have n tokens cached.
  if (n < toks.size())
    return toks[n];
  
  // Lex enough tokens to satisfy the requeest, and return the last token
  // lexed. If there aren't enough tokens, return nullptr.
  n = n - toks.size() + 1;
  while (n) {
    if (token* tok = lex.lex())
      toks.push_back(tok);
    else
      return nullptr;
    --n;
  }
  return toks.back();
}

token_kind
parser::lookahead()
{
  if (token* tok = peek())
    return tok->kind;
  else
    return eof_tok;
}

token_kind
parser::lookahead(int n)
{
  if (token* tok = peek(n))
    return tok->kind;
  else
    return eof_tok;
}

token*
parser::consume()
{
  assert(!toks.empty());

  // Take the current token.
  token* tok = toks.front();
  toks.pop_front();

  // Only refill the queue when needed. 
  if (toks.empty()) {
    if (token* next = lex.lex())
      toks.push_front(next);
  }

  return tok;
}

token*
parser::require(token_kind k)
{
  assert(lookahead() == k);
  return consume();
}

token*
parser::match(token_kind k)
{
  if (lookahead() == k)
    return consume();
  else {
    std::stringstream ss;
    ss << "expected '" << token::str(k) << '\'';
    throw std::runtime_error(ss.str().c_str());
  }
}

token*
parser::match_if(token_kind k)
{
  if (lookahead() == k)
    return consume();
  else
    return nullptr;
}

// -------------------------------------------------------------------------- //
// Entry point

decl*
parser::program()
{
  std::vector<stmt*> ss = statement_seq();
  return sema.on_program(ss);
}

// -------------------------------------------------------------------------- //
// Statement parsing

std::vector<stmt*>
parser::statement_seq()
{
  std::vector<stmt*> ss;
  while (!eof()) {
    stmt *s = statement();
    ss.push_back(s);
  }
  return ss;
}

stmt*
parser::statement()
{
  switch (lookahead()) {
    case var_kw:
      return declaration_statement();
    default:
      return expression_statement();
  }
}

stmt*
parser::declaration_statement()
{
  decl* d = declaration();
  return sema.on_declaration_statement(d);
}

stmt*
parser::expression_statement()
{
  expr* e = expression();
  match(semicolon_tok);
  return sema.on_expression_statement(e);
}


// -------------------------------------------------------------------------- //
// Declaration parsing

decl*
parser::declaration()
{
  switch (lookahead()) {
    case var_kw:
      return variable_declaration();
    default:
      break;
  }
  throw std::runtime_error("expected declaration");
}

decl*
parser::variable_declaration()
{
  require(var_kw);
  type* t = type_specifier();
  symbol* n = identifier();
  decl* var = sema.on_variable_declaration(t, n);
  match(eq_tok);
  expr* e = expression();
  sema.on_variable_completion(var, e);
  match(semicolon_tok);
  return var;
}

// -------------------------------------------------------------------------- //
// Type parsing

type*
parser::type_specifier()
{
  return simple_type_specifier();
}


type*
parser::simple_type_specifier()
{
  switch (lookahead()) {
    case bool_kw:
      consume();
      return sema.on_bool_type();
    case int_kw:
      consume();
      return sema.on_int_type();
  }
  throw std::runtime_error("expected simple-type-specifier");
}

// -------------------------------------------------------------------------- //
// Expression parsing

expr*
parser::expression()
{
  return additive_expression();
}

expr*
parser::additive_expression()
{
  expr* e1 = multiplicative_expression();
  while (true) {
    if (match_if(plus_tok)) {
      expr* e2 = multiplicative_expression();
      e1 = sema.on_add(e1, e2);
    }
    else if (match_if(minus_tok)) {
      expr* e2 = multiplicative_expression();
      e1 = sema.on_sub(e1, e2);
    }
    else
      break;
  }
  return e1;
}


expr*
parser::multiplicative_expression()
{
  expr* e1 = unary_expression();
  while (true) {
    if (match_if(times_tok)) {
      expr* e2 = unary_expression();
      e1 = sema.on_mul(e1, e2);
    }
    else if (match_if(div_tok)) {
      expr* e2 = unary_expression();
      e1 = sema.on_div(e1, e2);
    }
    else if (match_if(rem_tok)) {
      expr* e2 = unary_expression();
      e1 = sema.on_rem(e1, e2);
    }
    else
      break;
  }
  return e1;
}


expr*
parser::unary_expression()
{
  if (match_if(minus_tok)) {
    expr* e = unary_expression();
    return sema.on_neg(e);
  }
  else {
    return primary_expression();
  }
}

expr*
parser::primary_expression()
{
  switch (lookahead()) {
    case true_kw:
      return sema.on_true(consume());
    case false_kw:
      return sema.on_false(consume());
    case int_tok:
      return sema.on_int(consume());
    case id_tok:
      return id_expression();
    case lparen_tok: {
      consume();
      expr* e = expression();
      match(rparen_tok);
      return e;
    }
    default:
      break;
  }
  std::cout << peek() << '\n';
  throw std::runtime_error("expected primary-expression");
}

expr*
parser::id_expression()
{
  symbol* id = identifier();
  return sema.on_id(id);
}

// -------------------------------------------------------------------------- //
// Identifiers

symbol*
parser::identifier()
{
  token* id = match(id_tok);
  return sema.on_identifier(id);
}
