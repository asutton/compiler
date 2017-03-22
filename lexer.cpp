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
  buf.clear(); // Reset the character buffer.
  space(); // Consume preceding whitespace.
  while (first != limit) {
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
        return puncop(rem_tok);
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
  return new token(k);
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
  if (iter != kws->end())
    return new token(iter->second);

  // Otherwise, this is an identifier.
  symbol sym = syms->insert(buf);
  return new id_token(sym);
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
  return new int_token(std::stoi(buf));
}