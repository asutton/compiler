#pragma once

#include "tokens.hpp"
#include "lexer.hpp"
#include "translator.hpp"

#include <deque>
#include <vector>


struct stmt;
struct decl;
struct type;
struct expr;


/// The parser is responsible for transforming a sequence of tokens into
/// an abstract syntax tree. The grammar for the language is defined by the
/// various parsing functions.
struct parser
{
  parser(const keyword_table&, symbol_table&, context&, const std::string&);

  /// program -> statement-seq
  decl* program();

  // Statements

  /// statement-seq -> statement-seq statement | statement
  std::vector<stmt*> statement_seq();
  
  /// statement -> declaration-statement | expression-statement
  stmt* statement();

  /// declaration-statement -> declaration
  stmt* declaration_statement();

  /// expression-statement -> expression ';'
  stmt* expression_statement();


  // Declarations

  /// declaration -> variable-declaration
  decl* declaration();

  /// variable-declaration -> 'var' type-specifier identifier '=' expression ';'
  decl* variable_declaration();

  // Types

  /// type-specifier -> simple-type-specifier
  type* type_specifier();

  /// simple-type-specifier -> 'bool' | 'int'
  type* simple_type_specifier();

  // Expressions

  /// expression -> additive-expression
  expr* expression();

  /// additive-expression -> additive-expression '+' multiplicative-expression
  ///                      | additive-expression '-' multiplicative-expression
  ///                      | multiplicative-expression
  expr* additive_expression();

  /// multiplicative-expression -> multiplicative-expression '+' unary-expression
  ///                            | multiplicative-expression '-' unary-expression
  ///                            | unary-expression
  expr* multiplicative_expression();

  /// unary-expression -> '-' unary-expression
  ///                   | primary-expression
  expr* unary_expression();

  /// primary-expression -> 'true' 
  ///                     | 'false'
  ///                     | integer-literal
  ///                     | id-expression
  ///                     | '(' expression ')'
  expr* primary_expression();

  /// id-expression -> identifier
  expr* id_expression();

  /// identifier
  symbol* identifier();


private:
  /// Returns true if there is no more input.
  bool eof();

  /// Returns the current token.
  token* peek();

  /// Returns the nth token past the current token.
  token* peek(int);

  /// Returns the kind of the current token.
  token_kind lookahead();

  /// Returns the nth token past the current token.
  token_kind lookahead(int);

  /// Consume the current token and fetch the next into the queue.
  token* consume();

  /// Require that the token have the given kind and consume it.
  token* require(token_kind);
  
  /// If the current token has the given kind, consume it. Otherwise, diagnose
  /// the input as being ill-formed.
  token* match(token_kind);

  /// If the current token has the given kind, consume it. Otherwise, no
  /// action is taken.
  token* match_if(token_kind);

  /// The lexer.
  lexer lex;
  
  /// A queue of lexed tokens. This typically contains a single token or
  /// is empty. When looking past the current token, those tokens are added
  /// to the queue. We only fetch the next token when the queue is empty.
  std::deque<token*> toks;

  /// Semantic actions.
  translator sema;
};
