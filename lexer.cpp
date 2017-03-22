#include "lexer.hpp"

#include <cassert>
#include <cctype>


/// Returns true if c is a (decimal) digit.
static inline bool
is_digit(char c)
{
  return std::isdigit(c);
}

/// Returns true if c is a letter or underscore.
static inline bool
is_letter(char c)
{
  return std::isalpha(c) || c == '_';
}

/// Returns true if c is a letter or digit.
static inline bool
is_letter_or_digit(char c)
{
  return is_letter(c) || is_digit(c);
}


lexer::lexer(const keyword_table& kt, symbol_table& st, const char* f, const char* l)
  : kws(&kt), syms(&st), first(f), limit(l)
{ }

lexer::lexer(const keyword_table& kt, symbol_table& st, const std::string& str)
  : lexer(kt, st, &str[0], &str[0] + str.size())
{ }

lexer::~lexer()
{
  for (token* tok : toks)
    delete tok;
}

bool
lexer::eof() const
{
  return first == limit;
}

char
lexer::lookahead() const
{
  return eof() ? 0 : *first;
}

char
lexer::consume()
{
  assert(!eof());
  char c = *first++;
  buf.push_back(c);
  return c;
}

void
lexer::ignore()
{
  ++first;
}

token*
lexer::lex()
{
  // Quick exit if we're the end of file.
  if (eof())
    return nullptr;

  buf.clear(); // Reset the character buffer.
  space(); // Consume preceding whitespace.
  while (!eof()) {
    switch (*first) {
      case '(':
        return puncop(lparen_tok);
      case ')':
        return puncop(rparen_tok);
      case ';':
        return puncop(semicolon_tok);
      case ':':
        return puncop(colon_tok);
      case '?':
        return puncop(question_tok);
      case '+':
        return puncop(plus_tok);
      case '-':
        return puncop(minus_tok);
      case '*':
        return puncop(times_tok);
      case '/':
        return puncop(div_tok);
      case '%':
        return puncop(rem_tok);
      case '=':
        return puncop(eq_tok);
      default:
        if (is_digit(lookahead()))
          return integer();
        if (is_letter(lookahead()))
          return word();
        else 
          throw std::runtime_error("lexical error: invalid character");
    }
  }
  return nullptr;
}


void 
lexer::space()
{
  while (!eof() && std::isspace(lookahead()))
    ignore();
}

token*
lexer::puncop(token_kind k)
{
  ignore(); // We don't need the character.
  token* tok = new token(k);
  toks.push_back(tok);
  return tok;
}

token*
lexer::word()
{
  assert(is_letter(lookahead()));
  
  // Match id characters.
  consume();
  while (first != limit && is_letter_or_digit(lookahead()))
    consume();

  // Did we lex a keyword? If so, return a new token.
  auto iter = kws->find(buf);
  if (iter != kws->end()) {
    token *tok = new token(iter->second);
    toks.push_back(tok);
    return tok;
  }

  // Otherwise, this is an identifier.
  symbol* sym = syms->insert(buf);
  token* tok = new id_token(sym);
  toks.push_back(tok);
  return tok;
}

token*
lexer::integer()
{
  assert(is_digit(lookahead()));

  // Match digits.
  consume();
  while (first != limit && is_digit(lookahead()))
    consume();

  // Create the integer token.
  token* tok = new int_token(std::stoi(buf));
  toks.push_back(tok);
  return tok;
}